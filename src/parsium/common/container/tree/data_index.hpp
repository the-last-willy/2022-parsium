#pragma once

#include <cstddef>

namespace parsium {

class TreeDataIndex {
	std::size_t value_ = 0;

public:
	TreeDataIndex() = default;

	explicit
	TreeDataIndex(std::size_t value)
	: value_(value)
	{}

	auto value() const -> std::size_t {
		return value_;
	}
};

}
