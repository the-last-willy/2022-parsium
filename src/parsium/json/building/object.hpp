#pragma once

#include <parsium/common/tag/shallow.hpp>

namespace parsium {
namespace json {
namespace building {

class Object {
public:
	auto is_valid(decltype(shallow)) const -> bool;
};

}}}
