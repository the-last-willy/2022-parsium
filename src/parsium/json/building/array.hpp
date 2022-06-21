#pragma once

#include <parsium/common/tag/shallow.hpp>
#include <parsium/common/tag/undefined_behaviour.hpp>

#include <memory>
#include <vector>

namespace parsium {
namespace json {
namespace building {

class Element;

class Array {
	std::vector<Element> elements_;

public:
	auto at_or(std::size_t i, decltype(UB)) const -> const Element&;
	auto at_or(std::size_t i, decltype(UB)) -> Element&;

	auto elements() const -> const std::vector<Element>&;
	auto elements() -> std::vector<Element>&;

	auto create_at_end() -> Element&;

	auto is_valid(decltype(shallow)) const -> bool;
};

}}}
