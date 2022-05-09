#pragma once

#include "name.hpp"
#include "range_exclude.hpp"

#include <memory>
#include <utility>
#include <string>
#include <variant>

namespace parsium {
namespace mckeeman {

struct Literal {
	// Fuse char and range exclude together.
	std::variant<char, RangeExclude, std::string> content;
};

// Accessing.

inline
const std::string* optional_characters(const Literal& l) {
	return std::get_if<std::string>(&l.content);
}

inline
const RangeExclude* optional_range_exclude(const Literal& l) {
	return std::get_if<RangeExclude>(&l.content);
}

inline
const char* optional_singleton(const Literal& l) {
	return std::get_if<char>(&l.content);
}

// --

inline
bool does_accept(char codepoint, char c) {
	return c == codepoint;
}

inline
bool does_accept(const std::string& s, char c) {
	return s.size() > 0 and c == s.front();
}

inline
Literal characters_literal(std::string characters) {
	return Literal({std::move(characters)});
}

inline
Literal range_exclude_literal(Range range, Exclude exclude) {
	return Literal({range_exclude(std::move(range), std::move(exclude))});
}

inline
Literal singleton_literal(char codepoint) {
	return Literal({codepoint});
}

inline
bool does_accept(const Literal& l, char c) {
	return std::visit([c](auto&& a) -> bool {
		return does_accept(a, c);
	}, l.content);
}

}
}
