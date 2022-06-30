#pragma once

#include <cstddef>
#include <limits>

namespace parsium {

constexpr auto invalid_tree_node_index_value
= std::numeric_limits<std::size_t>::max();

class TreeNodeIndex {
	std::size_t value_ = invalid_tree_node_index_value;

public:
	constexpr
	TreeNodeIndex() = default;

	constexpr explicit
	TreeNodeIndex(std::size_t value)
	: value_(value)
	{}

	auto value() const -> std::size_t {
		return value_;
	}
};

constexpr auto invalid_tree_node_index
= TreeNodeIndex(invalid_tree_node_index_value);

inline
bool operator==(const TreeNodeIndex& i0, const TreeNodeIndex& i1) {
	return i0.value() == i1.value();
}

inline
bool is_valid(TreeNodeIndex i) {
	return i != invalid_tree_node_index;
}

}
