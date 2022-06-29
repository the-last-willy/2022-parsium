#pragma once

#include "parsium/common/container/tree/data_index.hpp"
#include "parsium/common/container/tree/node_index.hpp"

#include <parsium/common/tag/self.hpp>

#include <vector>

namespace parsium {

template<typename T>
struct TreeNode {
	std::vector<TreeNodeIndex> connections_;
	T data_;

	TreeNode(TreeNodeIndex parent, T&& data)
	: connections_({parent})
	, data_(std::move(data))
	{}

	auto parent_or(decltype(self)) const -> TreeNodeIndex {
		return connections_.front();
	}
};

}
