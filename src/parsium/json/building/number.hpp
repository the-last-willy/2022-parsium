#pragma once

#include "parsium/json/building/string.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
#include <parsium/common/tag/shallow.hpp>

#include <string>
#include <variant>

namespace parsium {
namespace json {
namespace building {

class Number {
	std::variant<std::monostate, float> data_;

public:
	Number() = default;

	Number(float f)
	{
		assign(f);
	}

	auto is_valid(decltype(shallow)) const -> bool;

	void assign(float f) {
		data_ = f;
	}

	std::string representation() const {
		if(holds_alternative<float>(data_)) {
			return std::to_string(std::get<float>(data_));
		} else {
			throw PreconditionViolation();
		}
	}
};

}}}
