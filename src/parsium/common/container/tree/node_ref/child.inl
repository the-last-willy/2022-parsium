#pragma once

#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
TreeNodeRef<T> TreeNodeRef<T>::child_or(decltype(UB), std::size_t i) const {
	return TreeNodeRef<T>(*tree_, node_->connections_[i + 1]);
}

}
