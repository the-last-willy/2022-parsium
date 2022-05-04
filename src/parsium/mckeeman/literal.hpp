#pragma once

#include "range_exclude.hpp"

#include <memory>
#include <utility>
#include <string>
#include <variant>

namespace parsium {
namespace mckeeman {

struct Literal {
	std::variant<char, RangeExclude, std::string> content;
};

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
