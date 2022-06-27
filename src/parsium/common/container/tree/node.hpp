#pragma once

#include "parsium/common/container/tree/node_index.hpp"

#include <vector>

namespace parsium {

template<typename Data>
struct Node {
	Data data;

	NodeIndex parent;
	std::vector<NodeIndex> children;
};

}
