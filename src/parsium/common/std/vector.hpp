#pragma once

#include <cassert>
#include <vector>

namespace parsium {

template<typename... T>
inline auto popped_front(std::vector<T...>&& v) -> std::vector<T...> {
	assert(!v.empty());
	v.erase(begin(v));
	return v;
}

}