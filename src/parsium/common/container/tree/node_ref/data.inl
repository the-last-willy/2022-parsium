#pragma once

#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
T& TreeNodeRef<T>::data() const {
	return node_->data_;
}

}
