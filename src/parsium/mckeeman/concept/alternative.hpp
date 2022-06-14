#pragma once

namespace parsium {
namespace mckeeman {

template<typename T>
requires requires(T&& a) { a.items(); }
decltype(auto) items(T&& a) {
	return a.items();
}

template<typename T>
concept Alternative_ = requires(T& t) {
	items(t);
};

}}
