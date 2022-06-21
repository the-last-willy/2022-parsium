#pragma once

#include "parsium/json/building/object.hpp"

namespace parsium {
namespace json {
namespace building {

inline
bool Object::is_valid(decltype(shallow)) const {
	return false;
}

}}}
