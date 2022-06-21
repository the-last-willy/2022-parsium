#pragma once

#include "parsium/json/building/number.hpp"

namespace parsium {
namespace json {
namespace building {

inline
bool Number::is_valid(decltype(shallow)) const {
	return false;
}

}}}
