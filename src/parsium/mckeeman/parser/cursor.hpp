#pragma once

#include "parsium/mckeeman/grammar.hpp"

#include <stdexcept>

namespace parsium {
namespace mckeeman {

struct Cursor {
	const Rule* rule = nullptr;
	std::size_t alternative = 0;
	std::size_t item = 0;
	std::size_t character = 0; // Rename into progression.
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

}
}
