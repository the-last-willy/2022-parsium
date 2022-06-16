#pragma once

#include "parsium/mckeeman/builder/characters.hpp"
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
	// Remove dependency to string.
	std::variant<Characters, Singleton, RangeExclude> content;

	template<typename T>
	auto dispatch_to(T&& t) const -> decltype(auto);
};

//

template<typename T>
Literal literal(T&& t) {
	return Literal({std::forward<T>(t)});
}

Literal literal(const char* str) {
	return Literal({Characters({std::move(str)})});
}

Literal literal(Range r) {
	return Literal({range_exclude(std::move(r))});
}

Literal literal(RangeExclude re) {
	return Literal({std::move(re)});
}

// --

inline
bool does_accept(const Literal& l, char c) {
	return std::visit([c](auto&& a) -> bool {
		return does_accept(a, c);
	}, l.content);
}

// --

inline
const Characters* characters_or(const Literal& l, std::nullptr_t) {
	return std::get_if<Characters>(&l.content);
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
