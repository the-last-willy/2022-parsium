#pragma once

#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
std::size_t TreeNodeRef<T>::child_count() const {
	return node_->connections_.size() - 1;
}

}
