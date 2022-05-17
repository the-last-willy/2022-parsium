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

inline
std::size_t depth(const Head& h) {
	return size(h.nested_cursors);
}

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
const Cursor& top(const Head& h) {
	return h.nested_cursors.back();
}

inline
Cursor& top(Head& h) {
	return h.nested_cursors.back();
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

// Moving.

inline
void move_to_alternative(Head& h, std::size_t alternative) {
	if(!is_empty(h)) {
		auto& t = top(h);
		t.alternative = alternative;
		t.item = 0;
		t.character = 0;
	}
}

inline
void move_to_next_item(Head& h) {
	if(!is_empty(h)) {
		move_to_next_item(top(h));
		unwind(h);
	}
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
					auto new_head = h;
					pop(new_head);
					move_to_next_item(new_head);
					// Feed it recursively until the symbol is consumed.
					fed_ = concatenation(std::move(fed_), fed(g, new_head, symbol));
				}
			}
			for(std::size_t ai = 0; ai < size(current_rule(cursor).alternatives); ++ai) {
				auto& alternative = current_rule(cursor).alternatives[ai];
				auto& first_item = alternative.items[0];
				if(auto literal = optional_literal(first_item)) {
					if(does_accept(*literal, symbol)) {
						auto& fh = fed_.emplace_back(h);
						move_to_alternative(fh, ai);
						progress(fh);
						unwind(fh);
					} else {
						// The alternative is rejected.
					}
				} else if(auto name = optional_name(first_item)) {
					// The symbol has to be fed to the named rule.
					auto next_head = h;
					move_to_alternative(next_head, ai);
					push(next_head, rule(g, *name));
					fed_ = concatenation(std::move(fed_), fed(g, next_head, symbol));
				}
			}
		} else if(!is_after_rule(cursor)) {
			if(auto name = optional_name(current_item(cursor))) {
				// Found a name and not symbol consumed yet.
				auto new_head = h;
				push(new_head, rule(g, *name));
				fed_ = concatenation(std::move(fed_), fed(g, std::move(new_head), symbol));
			} else if(auto literal = optional_literal(current_item(cursor))) {
				// Progresses in the current alternative.
				if(auto characters = optional_characters(*literal)) {
					if((*characters)[cursor.character] == symbol) {
						progress(h);
						fed_.push_back(std::move(h));
					}
				} else if(auto range_exclude = optional_range_exclude(*literal)) {
					if(does_accept(*range_exclude, symbol)) {
						progress(h);
						fed_.push_back(std::move(h));
					}
				} else if(auto singleton = optional_singleton(*literal)) {
					if(does_accept(*singleton, symbol)) {
						progress(h);
						fed_.push_back(std::move(h));
					}
				}
			}
		}
	}
	return fed_;
}

inline
bool is_accepting_from_current_alternative(const Grammar& g, const Head& h) {

}

inline
bool is_accepting(const Grammar& g, const Head& h) {
	if(is_empty(h)) {
		return true;
	} else {
		// If all remaining name items accept nothing then the head is accepting.
		auto& c = top(h);
		auto is_rule_accepting = false;
		if(is_before_rule(c)) {
			if(current_rule(c).does_accept_nothing) {
				// The head is before the rule and it accepts nothing, it can be popped.
				is_rule_accepting = true;
			} else {

			}
		}
		if(!skip_rule) {
			// Checks all alternatives.
			auto& alternative = current_alternative(c);
			for(std::size_t i = c.item; i < size(alternative.items); ++i) {
				auto& item = alternative.items[i];
				if(auto literal = literal_or(item, nullptr)) {
					// A literal
					return false;
				} else if(auto name = name_or(item, nullptr)) {
					auto& r = rule(g, *name);
					if(!r.does_accept_nothing) {
						return false;
					}
				}
			}
		}
	}
}

}
}
