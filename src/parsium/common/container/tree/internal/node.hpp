#pragma once

#include <parsium/common/tag/self.hpp>

#include <limits>
#include <vector>

namespace parsium {

constexpr auto invalid_tree_node_id = std::numeric_limits<std::size_t>::max();

template<typename T>
struct TreeNodeInternals {
	std::vector<std::size_t> connections_;
	T data_;

	TreeNodeInternals(std::size_t parent_id, T&& data)
	: connections_({parent_id})
	, data_(std::move(data))
	{}
};

}
