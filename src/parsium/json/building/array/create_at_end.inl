#pragma once

#include "parsium/json/building/array.hpp"
#include "parsium/json/building/element.hpp"

namespace parsium {
namespace json {
namespace building {

inline
Element& Array::create_at_end() {
	return elements_.emplace_back();
}

}}}
