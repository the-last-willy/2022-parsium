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

/**
 * It's not possible to represent the base rule with only cursors.
 * Do we want a base rule inside the head then ?
 *
 * How to distinguish the cursor being before and after the base rule ?
 * Maybe set the base rule to null to signify it's outside the base rule.
 *
 * \section Invariants
 *
 * - A `Head` represents a path uniquely.
 *
 * - Should the head always be before a literal ?
 * How to represent a head on the base rule ?
 * How to represent a head after the last literal ?
 *
 * - Should the head be able to go past the last item in its alternative ?
 * That would be redundant with the head being popped and moved to the next item ?
 */
struct Head {
	std::vector<Cursor> nested_cursors;
	std::size_t character_index = 0;
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
Head nested(Head h, const builder::Alternative& a) {
	h.nested_cursors.emplace_back(cursor(a));
	return h;
}

inline
Head unnested(Head h) {
	if(is_empty(h)) {
		return h;
	} else {
		pop(h);
		return h;
	}
}

inline
const Cursor& top_or(const Head& h, UndefinedBehaviourTag) {
	return h.nested_cursors.back();
}

inline
Cursor& top_or(Head& h, UndefinedBehaviourTag) {
	return h.nested_cursors.back();
}

inline
void move_to_next_item(Head& h) {
	if(!is_empty(h)) {
		auto t = &top_or(h, UB);
		t->item_index += 1;
		// Pops and increases the item index as long as the head is at the last item.
		while(t->item_index == size(items(*t->alternative))) {
			pop(h);
			if(is_empty(h)) {
				// Can't go past an empty head.
				break;
			} else {
				// Goes to the next item of the parent rule.
				t = &top_or(h, UB);
				t->item_index += 1;
			}
		}
	}
}

inline
Head moved_to_next_item(Head h) {
	move_to_next_item(h);
	return h;
}

inline
void move_to_next_character(Head& h) {
	if(!is_empty(h)) {
		auto& top = top_or(h, UB);
		auto& item = current_item(top);
		if(auto literal = literal_or(item, nullptr)) {
			if(auto characters = characters_or(*literal, nullptr)) {
				h.character_index += 1;
				if(h.character_index == size(*characters)) {
					// All characters have been read.
					h.character_index = 0;
					move_to_next_item(h);
				}
			} else {
				// Either a range exclude or a singleton which consumes a single character.
				move_to_next_item(h);
			}
		} else {
			throw PreconditionViolation();
		}
	}
}

inline
Head moved_to_next_character(Head h) {
	move_to_next_character(h);
	return h;
}

}
}
