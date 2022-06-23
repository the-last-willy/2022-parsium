#pragma once

#include <parsium/common/tag/shallow.hpp>

#include <string>

namespace parsium {
namespace json {
namespace building {

class String {
	std::string characters_;

public:
	auto is_valid(decltype(shallow)) const -> bool;

	auto characters() const -> const std::string&;
	auto characters() -> std::string&;

	auto assign(const char* c) -> void;
};

}}}

#include "parsium/json/building/string/assign.inl"
#include "parsium/json/building/string/characters.inl"
#include "parsium/json/building/string/is_valid.inl"
