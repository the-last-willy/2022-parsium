#pragma once

#include "parsium/mckeeman/builder/name.hpp"
#include "parsium/mckeeman/builder/range_exclude.hpp"
#include "parsium/mckeeman/builder/range_exclude/does_accept.hpp"

#include <parsium/mckeeman/common/singleton.hpp>

#include <string>
#include <variant>

namespace parsium {
namespace mckeeman {
namespace builder {

class Literal {
public:
	// Fuse singleton and range exclude together, or with string.
	std::variant<Singleton, RangeExclude, std::string> content;
};

//

template<typename T>
Literal literal(T&& t) {
	return Literal({std::forward<T>(t)});
}

Literal literal(const char* str) {
	return Literal({std::string(str)});
}

Literal literal(Range r) {
	return Literal({range_exclude(std::move(r))});
}

Literal literal(RangeExclude re) {
	return Literal({std::move(re)});
}

// --

inline
bool does_accept(Singleton s, char c) {
	return c == s;
}

inline
bool does_accept(const std::string& s, char c) {
	return s.size() > 0 && c == s.front();
}

inline
bool does_accept(const Literal& l, char c) {
	return std::visit([c](auto&& a) -> bool {
		return does_accept(a, c);
	}, l.content);
}

// --

inline
const std::string* characters_or(const Literal& l, std::nullptr_t) {
	return std::get_if<std::string>(&l.content);
}

inline
const RangeExclude* range_exclude_or(const Literal& l, std::nullptr_t) {
	return std::get_if<RangeExclude>(&l.content);
}

inline
const Singleton* singleton_or(const Literal& l, std::nullptr_t) {
	return std::get_if<Singleton>(&l.content);
}

}}}
