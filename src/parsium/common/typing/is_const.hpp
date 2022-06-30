#pragma once

#include <type_traits>

namespace parsium {

template<typename T>
struct IsTypeConstImpl {
	static constexpr auto value = std::is_const_v<T>;
};

template<typename T>
constexpr auto is_type_const = IsTypeConstImpl<T>::value;

}
