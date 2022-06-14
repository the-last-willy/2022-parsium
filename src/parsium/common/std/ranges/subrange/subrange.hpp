#pragma once

#include <cstddef>
#include <utility>

namespace parsium {

template<typename Iterator, typename Sentinel>
struct Subrange {
	Iterator iterator;
	Sentinel sentinel;

//	auto& operator[](std::ptrdiff_t i) {
//		// Very unsafe.
//		return *(iterator + i);
//	}
};

template<typename I, typename S>
auto subrange(I i, S s) {
	return Subrange<I, S>{std::move(i), std::move(s)};
}

template<typename... S>
const auto& begin(const Subrange<S...>& s) {
	return s.iterator;
}

template<typename... S>
const auto& end(const Subrange<S...>& s) {
	return s.sentinel;
}

}