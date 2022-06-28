#pragma once

#include "parsium/common/container/tree/data_index.hpp"
#include "parsium/common/container/tree/node_index.hpp"

#include <vector>

namespace parsium {

struct TreeNode {
	std::vector<TreeNodeIndex> connections;
	TreeDataIndex data;
};

}
