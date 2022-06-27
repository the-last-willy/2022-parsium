#pragma once

#include <type_traits>

namespace parsium {

template<typename T, bool b>
struct ConstIfImpl {
	using Type = std::conditional_t<b, const T, T>;
};

template<typename T, bool b>
using ConstIf = typename ConstIfImpl<T, b>::Type;

}
