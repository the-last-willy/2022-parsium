#pragma once

#include "parsium/json/building/string.hpp"

namespace parsium {
namespace json {
namespace building {

inline
void String::assign(const char* c) {
	characters_ = c;
}

}}}
