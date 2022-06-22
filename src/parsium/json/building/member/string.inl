#pragma once

#include "parsium/json/building/member.hpp"

namespace parsium {
namespace json {
namespace building {

inline
const String& Member::string() const {
	return string_;
}

inline
String& Member::string() {
	return string_;
}

}}}
