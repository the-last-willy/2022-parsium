#pragma once

#include <cstddef>

namespace parsium {

class TreeNodeIndex {
	std::size_t value_ = 0;

public:
	TreeNodeIndex() = default;

	explicit
	TreeNodeIndex(std::size_t value)
	: value_(value)
	{}

	auto value() const -> std::size_t {
		return value_;
	}
};

}
