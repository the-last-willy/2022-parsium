#pragma once

#include "literal.hpp"
#include "name.hpp"

#include <variant>

namespace parsium {
namespace mckeeman {

struct Item {
	template<typename T>
	Item(T&& t)
	: content(std::forward<T>(t))
	{}

	std::variant<Literal, Name> content;
};

bool has_literal(const Item& i) {
	return std::holds_alternative<Literal>(i.content);
}

bool has_name(const Item& i) {
	return std::holds_alternative<Name>(i.content);
}

}
}
