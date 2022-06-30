#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/node_id.hpp"

#include <parsium/common/tag/self.hpp>
#include <parsium/common/tag/undefined_behaviour.hpp>

namespace parsium {

template<typename T>
TreeNodeIndex TreeNode<T>::parent_index_or(decltype(self)) const {
	return tree().subtree_or(UB, index()).connections_.front();
}

}
