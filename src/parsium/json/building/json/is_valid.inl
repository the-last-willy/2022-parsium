#pragma once

#include "parsium/json/building/json.hpp"

namespace parsium {
namespace json {
namespace building {

inline
bool Json::is_valid(decltype(shallow)) const {
	return false;
}

}}}
