#pragma once

#include "parsium/json/building/member.hpp"

namespace parsium {
namespace json {
namespace building {

inline
const Element& Member::element() const {
	return element_;
}

inline
Element& Member::element() {
	return element_;
}

}}}
