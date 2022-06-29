#pragma once

#include <cstddef>
#include <limits>

namespace parsium {

constexpr auto invalid_tree_data_index_value
= std::numeric_limits<std::size_t>::max();

class TreeDataIndex {
	std::size_t value_ = invalid_tree_data_index_value;

public:
	constexpr
	TreeDataIndex() = default;

	constexpr explicit
	TreeDataIndex(std::size_t value)
	: value_(value)
	{}

	auto value() const -> std::size_t {
		return value_;
	}
};

inline
bool is_valid(TreeDataIndex i) {
	return i.value() != invalid_tree_data_index_value;
}

constexpr auto invalid_tree_data_index
= TreeDataIndex(invalid_tree_data_index_value);

}
