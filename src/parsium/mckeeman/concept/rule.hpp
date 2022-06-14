#pragma once

#include "name.hpp"
#include "traits.hpp"

namespace parsium {
namespace mckeeman {

template<typename T>
requires requires(T&& a) { a.alternatives(); }
decltype(auto) alternatives(T&& a) {
	return a.alternatives();
}

template<typename T>
requires requires(T&& a) { a.grammar(); }
decltype(auto) grammar(T&& a) {
	return a.grammar();
}

template<typename T>
requires requires(T&& a) { a.name(); }
decltype(auto) name(T&& a) {
	return a.name();
}

template<typename T>
concept Rule_ = requires(T r) {
	typename Traits<T>;

	// alternatives(r);
	// { grammar(r) } /* -> Grammar */;
	// { name(r) } -> Name;
};

}}
