#pragma once

#include "parsium/json/building/array.hpp"
#include "parsium/json/building/element.hpp"

#include <memory>
#include <vector>

namespace parsium {
namespace json {
namespace building {

inline
const Element& Array::at_or(std::size_t i, decltype(UB)) const {
	return elements_[i];
}

inline
Element& Array::at_or(std::size_t i, decltype(UB)) {
	return elements_[i];
}

}}}
