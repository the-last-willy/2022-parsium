#pragma once

#include "literal.hpp"
#include "name.hpp"

#include <variant>

namespace parsium {
namespace mckeeman {

struct Item {
	Item(char c)
	: content(Literal({c}))
	{}

	Item(Name n)
	: content(std::move(n))
	{}

	Item(Range r)
	: Item(range_exclude(r))
	{}

	Item(RangeExclude re)
	: content(Literal({std::move(re)}))
	{}

	Item(std::string s)
	: content(Literal({std::move(s)}))
	{}

	std::variant<Literal, Name> content;
};

// --

inline
const Literal& literal(const Item& i) {
	return std::get<Literal>(i.content);
}

inline
bool has_literal(const Item& i) {
	return std::holds_alternative<Literal>(i.content);
}

inline
const Literal* optional_literal(const Item& i) {
	return std::get_if<Literal>(&i.content);
}

inline
bool has_name(const Item& i) {
	return std::holds_alternative<Name>(i.content);
}

inline
const Name* optional_name(const Item& i) {
	return std::get_if<Name>(&i.content);
}

}
}
