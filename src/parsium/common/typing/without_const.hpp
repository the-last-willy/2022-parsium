#pragma once

#include <type_traits>

namespace parsium {

template<typename T>
struct WithoutConstImpl {
	using Type = std::remove_const_t<T>;
};

template<typename T>
using WithoutConst = typename WithoutConstImpl<T>::Type;

}
