#pragma once

#include <parsium/common/tag/undefined_behaviour.hpp>

#include <memory>
#include <vector>

namespace parsium {
namespace json {
namespace building {

class Element;

class Array {
	std::vector<std::unique_ptr<Element>> elements_;
public:

	auto at_or(std::size_t i, decltype(UB)) const -> const Element&;
	auto at_or(std::size_t i, decltype(UB)) -> Element&;
};

inline
const Element& Array::at_or(std::size_t i, decltype(UB)) const {
	return *elements_[i];
}

inline
Element& Array::at_or(std::size_t i, decltype(UB)) {
	return *elements_[i];
}

}}}
