#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/node_id.hpp"

#include <span>

namespace parsium {

template<typename T>
auto TreeNode<T>::children_indices() const -> std::span<QualifiedIndex> {
	auto& internal = tree().subtree_or(UB, index());
	return std::span();
}

}
