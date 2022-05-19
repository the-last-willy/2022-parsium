#pragma once

#include "cursor.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
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
Cursor& top_or(Head& h, common::UndefinedBehaviourTag) {
	return h.nested_cursors.back();
}

inline
std::vector<Head> fed_nothing(const Grammar& g, Head h) {
	if(is_empty(h)) {
		return {};
	} else {
		auto result = std::vector<Head>();
		auto& top = top_or(h, common::ub);
		if(top.character_index == 0) {
			// The cursor is not inside a literal,
			// otherwise it has to be fed a symbol to progress.
			auto& next_item = top.alternative->items[top.item_index];
			if(const Name* name = name_or(next_item, nullptr)) {
				if(rule(g, name).does_accept_nothing) {
					if(is_at_last_item(top)) {
						// The cursor goes out of the alternative.
					} else {
						
					}
				}
			}
		}
		return result;
	}
}

}
}
