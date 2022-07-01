#pragma once

#include "parsium/common/container/tree/node_ptr.hpp"
#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
TreeNodeRef<T> TreeNodePtr<T>::operator*() const {
	return TreeNodeRef<T>(*tree_, id_);
}

}
