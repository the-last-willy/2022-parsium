#pragma once

#include "traits.hpp"

namespace parsium {
namespace mckeeman {

template<typename T>
requires requires(T&& a) { a.rules(); }
decltype(auto) rules(T&& a) {
	return a.rules();
}

template<typename T>
concept Grammar_ = requires(const T r) {
	typename Traits<T>;

	rules(r);
};

}}
