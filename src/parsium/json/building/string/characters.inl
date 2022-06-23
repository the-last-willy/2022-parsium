#pragma once

#include "parsium/json/building/string.hpp"

namespace parsium {
namespace json {
namespace building {

inline
const std::string& String::characters() const {
	return characters_;
}

inline
std::string& String::characters() {
	return characters_;
}

}}}
