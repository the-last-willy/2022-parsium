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
 * A cursor can ambiguously be represented as before or after something.
 * It has been chosen to exclude the later.
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
	const Rule* rule_ = nullptr;
	std::size_t alternative_index_ = 0;
	std::size_t item_index_ = 0;
	std::size_t character_index_ = 0; // Rename into progression.

	// Rule.

	const Rule& rule() const {
		return *rule_;
	}

	bool is_inside_rule() const {
		return rule_ != nullptr;
	}

	// Alternative.

	const Alternative& alternative() const {
		return rule().alternatives[alternative_index_];
	}

	bool is_inside_alternative() const {
		return item_index_ > 0;
	}

	bool move_to_next_item() {

	}

	// Item.

	const Item& item() const {
		return alternative().items[item_index_];
	}

	bool is_inside_item() const {
		return character_index_ == 0;
	}

	bool move_to_next_character() {

	}
};

// Pseudo ctor.

inline
Cursor cursor(const Rule& r) {
	auto cursor_ = Cursor();
	cursor_.rule = &r;
	return cursor_;
}

// Accessing.

inline
bool is_inside_item(const Cursor& c) {
	
}

inline
const Rule& current_rule(const Cursor& c) {
	return *c.rule;
}

inline
const Alternative& current_alternative(const Cursor& c) {
	return current_rule(c).alternatives[c.alternative];
}

inline
const Item& current_item(const Cursor& c) {
	return current_alternative(c).items[c.item];
}

inline
std::size_t remaining_item_count(const Cursor& c) {
	if(c.item == 0) {
		// The cursor is not engaged in any alternative yet.
		// The alternative of which to return the item count is thus undetermined.
		throw common::PreconditionViolation();
	}

	// If the cursor is inside an item should it be counted ?
	// The current answer is yes.


}

// Positioning.

inline
bool is_before_rule(const Cursor& c) {
	return c.alternative == 0 && c.item == 0 && c.character == 0;
}

inline
bool is_after_rule(const Cursor& c) {
	return c.alternative == size(c.rule->alternatives);
}

inline
bool is_before_alternative(const Cursor& c) {
	return c.item == 0 && c.character == 0;
}

inline
bool is_after_alternative(const Cursor& c) {
	return c.item == size(current_alternative(c).items);
}

inline
bool is_before_item(const Cursor& c) {
	return c.character == 0;
}

inline
bool is_after_item(const Cursor& c) {
	auto& item = current_item(c);
	if(has_literal(item)) {
		auto& literal = std::get<Literal>(item.content);
		if(auto string = std::get_if<std::string>(&literal.content)) {
			return c.character >= size(*string);
		} else {
			return c.character > 0;
		}
	} else if(has_name(item)) {
		return c.character > 0;
	} else {
		throw std::logic_error("wtf");
	}
}

// Moving.

inline
void progress(Cursor& c) {
	c.character += 1;
}

inline
void move_to_next_character(Cursor& c) {
	progress(c);
}

inline
void move_to_next_item(Cursor& c) {
	c.item += 1;
	c.character = 0;
}

inline
void move_to_rule_end(Cursor& c) {
	c.alternative = size(current_rule(c).alternatives);
	c.item = 0;
	c.character = 0;
}

inline
bool is_accepting(const Grammar& g, const Cursor& c) {
	if(c.character > 0) {
		// The cursor started reading a literal item and is not finished.
		return false;
	} else if(c.item > 0) {
		// The cursor started reading an alternative and hasn't finished yet.
		// All remaining items need to be accepting without consuming a symbol.
		for(std::size_t i = 0; i < )
	}
}

}
}
