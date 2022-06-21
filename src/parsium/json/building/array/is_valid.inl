#pragma once

#include "parsium/json/building/array.hpp"

namespace parsium {
namespace json {
namespace building {

inline
bool Array::is_valid(decltype(shallow)) const {
	return false;
}

}}}
