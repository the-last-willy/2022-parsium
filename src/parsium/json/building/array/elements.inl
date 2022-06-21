#pragma once

#include "parsium/json/building/array.hpp"
#include "parsium/json/building/element.hpp"

namespace parsium {
namespace json {
namespace building {

inline
const std::vector<Element>& Array::elements() const {
	return elements_;
}

inline
std::vector<Element>& Array::elements() {
	return elements_;
}

}}}
