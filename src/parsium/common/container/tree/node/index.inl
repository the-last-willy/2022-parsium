#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/node_id.hpp"

namespace parsium {

template<typename T>
TreeNodeIndex TreeNode<T>::index() const {
	return index_;
}

}
