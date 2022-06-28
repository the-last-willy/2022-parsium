#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/subtree.hpp"

#include <vector>

namespace parsium {

template<typename T>
class Tree {
	std::vector<T> data_;
	std::vector<TreeNode> nodes_;

public:
	auto data(TreeDataIndex i) const -> const T& {
		return data_[i.value()];
	}

	auto data(TreeDataIndex i) -> T& {
		return data_[i.value()];
	}

	auto subtree(TreeNodeIndex i) const -> Subtree<const T> {
		return Subtree(*this, i);
	}

	auto subtree(TreeNodeIndex i) -> Subtree<T> {
		return Subtree(*this, i);
	}
};

}
