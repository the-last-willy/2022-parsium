#pragma once

#include "parsium/common/container/tree/internal/node.hpp"
#include "parsium/common/container/tree/node_id.hpp"

#include <vector>

namespace parsium {

template<typename T>
struct TreeInternals {
	std::vector<TreeNodeInternals<T>> nodes_;
	std::size_t root_id_ = invalid_tree_node_index_value;
};



}
