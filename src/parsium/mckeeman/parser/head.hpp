#pragma once

#include "cursor.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
#include <parsium/common/std/vector/concatenation.hpp>
#include <parsium/common/tag/undefined_behaviour.hpp>

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

inline
bool is_empty(const Head& h) {
	return depth(h) == 0;
}

inline
void pop(Head& h) {
	if(!is_empty(h)) {
		h.nested_cursors.pop_back();
	}
}

inline
Cursor& top_or(Head& h, UndefinedBehaviourTag) {
	return h.nested_cursors.back();
}

inline
std::vector<Head> fed_nothing(const Grammar& g, Head h) {
	auto result = std::vector<Head>();
	if(!is_empty(h)) {
		auto& top = top_or(h, UB);
		if(top.character_index == 0) {
			// The cursor is not inside a literal,
			// otherwise it has to be fed a symbol to progress.
			auto& next_item = top.alternative->items[top.item_index];
			if(const Name* name = name_or(next_item, nullptr)) {
				// The cursor is inside a name.
				auto& rule_ = rule(g, *name);
				if(rule_.does_accept_nothing) {
					if(is_at_last_item(top)) {
						// The cursor goes out of the alternative.
						auto new_head = h;
						pop(h);
						result = fed_nothing(g, std::move(new_head));
					} else {
						auto new_head = h;
						top_or(new_head, UB).item_index += 1;
						result = fed_nothing(g, std::move(new_head));
					}
				}
				for(auto& alternative : rule_.alternatives) {
					auto alternative_head = h;
					alternative_head.nested_cursors.push_back(cursor(alternative));
					result = concatenation(std::move(result),
						fed_nothing(g, std::move(alternative_head)));
				}
			}
		}
	}
	result.emplace_back(std::move(h));
	return result;
}

inline
std::vector<Head> fed(const Grammar& g, Head h, char symbol) {
	auto result = std::vector<Head>();
	if(!is_empty(h)) {

	}
	return result;
}

}
}
