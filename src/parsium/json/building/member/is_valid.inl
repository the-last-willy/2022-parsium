#pragma once

#include "parsium/json/building/member.hpp"

#include <parsium/common/tag/shallow.hpp>

namespace parsium {
namespace json {
namespace building {

inline
bool Member::is_valid(decltype(shallow)) const {
	return true;
}

}}}
