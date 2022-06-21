#pragma once

#include "parsium/json/building/string.hpp"

namespace parsium {
namespace json {
namespace building {

inline
bool String::is_valid(decltype(shallow)) const {
	return false;
}

}}}
