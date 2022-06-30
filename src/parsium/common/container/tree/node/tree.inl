#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/tree.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>

namespace parsium {

template<typename T>
auto TreeNode<T>::tree() const -> QualifiedTree& {
	return *tree_;
}

}
