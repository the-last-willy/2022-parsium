#pragma once

#include "parsium/json/building/element.hpp"
#include "parsium/json/building/string.hpp"

#include <parsium/common/tag/shallow.hpp>

#include <string>
#include <variant>

namespace parsium {
namespace json {
namespace building {

class Member {
	Element element_;
	String string_;

public:
	auto element() const -> const Element&;
	auto element() -> Element&;
	auto string() const -> const String&;
	auto string() -> String&;

	auto is_valid(decltype(shallow)) const -> bool;
};

}}}
