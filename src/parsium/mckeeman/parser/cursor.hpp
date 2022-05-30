#pragma once

#include "parsium/mckeeman/grammar.hpp"

#include <parsium/common/exception/precondition_violation.hpp>

#include <stdexcept>

namespace parsium {
namespace mckeeman {

/**
 *
 *
 * \section Invariants
 *
 * - A cursor can ambiguously be represented as before or after something.
 * It has been chosen to exclude the later.
 *
 * - Representing whether a cursor is before an alternative or before a rule is a pain.
 * Therefore a cursor must always be as precise as possible.
 * So it cannot be before a rule.
 *
 * - `rule` should probably be not null ?
 * Otherwise it would propagates the need to check for it to be not null.
 * Which is a pain...
 * But that would prevent from having a default constructor.
 * Which is also a pain...
 *
 * - `alternative` should be less than the number of alternatives in the rule.
 * Should a cursor be able to represent being
 *
 * - `item` should be strictly less
 *
 * \section ?
 *
 * - Should a cursor be able to represent being after a rule ?
 *
 * If so, that would make for an additional check for the caller.
 *
 * Otherwise, operations need to be careful not to break that invariant,
 * and thus need to conveyed to the caller that the operation cannot be done.
 * That
 *
 * - Should the point on `Rule` be const ?
 * It's used for parsing, which shouldn't change the grammar, but still ?
 *
 * - Should cursors have finer representations, like `RuleCursor`, `AlternativeCursor` and so on ?
 * The type would that way convey more meaning and some invariants could be segregated further.
 *
 * Which way should the composition be done ?
 * `Character` inside `Item` inside `Alternative` inside `Rule`, or the opposite ?
 *
 * The former should always be accompanied by context because knowing the character without knowing the item, the alternative and the rule doesn't make much sense.
 * It would be equivalent to, sort of, have the full cursor.
 * Therefore would it make for a proper abstraction ?
 *
 * The later is however sufficient on that aspect.
 * In an alternative cursor, the cursor is before the alternative as per the invariant since the cursor is not inside an item.
 * Same thing item and character.
 * It would at least split invariants over multiple classes without need for additional context.
 */
struct Cursor {
	const Alternative* alternative = nullptr;
	std::size_t item_index = 0;
};

inline
Cursor cursor(const Alternative& a) {
	auto result = Cursor();
	result.alternative = &a;
	return result;
}

inline
bool is_at_last_item(const Cursor& c) {
	return c.item_index + 1 == size(c.alternative->items);
}

inline
const Item& current_item(const Cursor& c) {
	return c.alternative->items[c.item_index];
}

}
}
