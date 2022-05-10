#pragma once

#include "cursor.hpp"

#include <iterator>
#include <memory>
#include <vector>

namespace parsium {
namespace mckeeman {

struct Head {
	std::vector<Cursor> nested_cursors;
};

// Testing.

inline
bool is_empty(const Head& h) {
	return h.nested_cursors.empty();
}

inline
void pop(Head& h) {
	h.nested_cursors.pop_back();
}

inline
Cursor& push(Head& h, const Rule& r) {
	return h.nested_cursors.emplace_back(cursor(r));
}

inline
Cursor& top(Head& h) {
	return h.nested_cursors.back();
}

inline
std::size_t depth(const Head& h) {
	return size(h.nested_cursors);
}

// Modifying ?

inline
void unwind(Head& h) {
	// An empty head is accepting,
	if(!is_empty(h)) {
		auto th = &top(h);
		if(is_after_rule(*th)) {
			// The head is rejecting.
			while(depth(h) > 1) {
				pop(h);
			}
			move_to_rule_end(top(h));
		} else {
			if(!is_after_alternative(*th) && is_after_item(*th)) {
				move_to_next_item(*th);
			}

			while(is_after_alternative(*th)) {
				pop(h);
				if(is_empty(h)) {
					break;
				} else {
					th = &top(h);
					move_to_next_item(*th);
					if(!is_after_alternative(*th) && is_after_item(*th)) {
						move_to_next_item(*th);
					}
				}
			}
		}
	}
}

inline
void progress(Head& h) {
	progress(top(h));
	unwind(h);
}

// Feeding.

inline
std::vector<Head> concatenation(std::vector<Head> hs0, std::vector<Head> hs1) {
	hs0.insert(end(hs0),
		std::make_move_iterator(begin(hs1)),
		std::make_move_iterator(end(hs1)));
	return hs0;
}

inline
std::vector<Head> fed(const Grammar& g, Head h, char symbol) {
	auto fed_ = std::vector<Head>();
	if(is_empty(h)) {
		// The empty head is accepting.
		// Consuming a symbol from the empty state is rejected.
		// The head is ignored and therefore discarded.
	} else {
		auto& cursor = top(h);
		if(is_before_rule(cursor)) {
			// Finds alternatives that would accept the symbol.
			if(current_rule(cursor).does_accept_nothing) {
				// Rule is accepted but no symbol is consumed yet.
				// If depth is 1, then no symbol can be consumed and the head is rejected.
				if(depth(h) > 1) {
					auto& fh = fed_.emplace_back(h);
					pop(fh);
					move_to_next_item(top(fh));
					unwind(fh);
					// Feed it recursively until the symbol is consumed.
					fed_ = concatenation(std::move(fed_), fed(g, fh, symbol));
				}
			}
			for(std::size_t ai = 0; ai < size(current_rule(cursor).alternatives); ++ai) {
				auto& alternative = current_rule(cursor).alternatives[ai];
				auto& first_item = alternative.items[0];
				if(auto literal = optional_literal(first_item)) {
					if(does_accept(*literal, symbol)) {
						auto& fh = fed_.emplace_back(h);
						progress(fh);
						unwind(fh);
					} else {
						// The alternative is rejected.
					}
				} else if(auto name = optional_name(first_item)) {
					// The symbol has to be fed to the named rule.
					auto next_head = h;
					push(next_head, rule(g, *name));
					fed_ = concatenation(std::move(fed_), fed(g, next_head, symbol));
				}
			}
		} else if(!is_after_rule(cursor)) {
			if(auto name = optional_name(current_item(cursor))) {
				// Found a name and not symbol consumed yet.
				push(h, rule(g, *name));
				fed_ = concatenation(std::move(fed_), fed(g, std::move(h), symbol));
			} else if(auto literal = optional_literal(current_item(cursor))) {
				// Progresses in the current alternative.
				if(auto characters = optional_characters(*literal)) {
					if((*characters)[cursor.character] == symbol) {
						progress(h);
					}
				} else if(auto range_exclude = optional_range_exclude(*literal)) {
					if(does_accept(*range_exclude, symbol)) {
						progress(h);
					}
				} else if(auto singleton = optional_singleton(*literal)) {
					if(does_accept(*singleton, symbol)) {
						progress(h);
					}
				}
			}
		}
	}
	return fed_;
}

}
}
