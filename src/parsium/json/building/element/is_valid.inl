#pragma once

#include "parsium/json/building/element.hpp"

#include <type_traits>

namespace parsium {
namespace json {
namespace building {

inline
bool Element::is_valid(decltype(shallow)) const {
	// return std::holds_alternative<std::monostate>(content_);
	return true;
}

}}}
