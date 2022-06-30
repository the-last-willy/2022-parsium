#pragma once

#include "parsium/common/container/tree/node_ptr.hpp"
#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
TreeNodePtr<T> TreeNodeRef<T>::parent_or(decltype(nullptr)) const {
	return TreeNodePtr<T>(*tree_, node_->connections_[0]);
}

}
