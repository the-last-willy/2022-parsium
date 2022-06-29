#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/subtree.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>

#include <vector>

namespace parsium {

template<typename T>
class Tree {
	std::vector<TreeNode<T>> nodes_;
	TreeNodeIndex root_ = invalid_tree_node_index;

public:

	// Access.

	auto data_or(decltype(UB), TreeDataIndex i) const -> const T& {
		auto node_index = TreeNodeIndex(i.value());
		return nodes_[node_index.value()].data;
	}

	auto data_or(decltype(UB), TreeDataIndex i) -> T& {
		auto node_index = TreeNodeIndex(i.value());
		return nodes_[node_index.value()].data;
	}

	auto root_index() const -> TreeNodeIndex {
		return root_;
	}

	auto subtree_or(decltype(UB), TreeNodeIndex i) const -> Subtree<const T> {
		return Subtree(*this, i);
	}

	auto subtree_or(decltype(UB), TreeNodeIndex i) -> Subtree<T> {
		return Subtree(*this, i);
	}

	//

	auto construct_root_or(decltype(UB), T&& data) -> Subtree<T> {
		root_ = TreeNodeIndex(nodes_.size());
		nodes_.push_back(TreeNode(root_, std::move(data)));
		return subtree(*this, root_);
	}

	auto destroy_root() -> void {
		nodes_.clear();
	}
};

}
