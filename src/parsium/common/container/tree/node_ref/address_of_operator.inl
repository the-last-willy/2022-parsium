#pragma once

#include "parsium/common/container/tree/node_ref.hpp"
#include "parsium/common/container/tree/node_ptr.hpp"

namespace parsium {

template<typename T>
TreeNodePtr<T> TreeNodeRef<T>::operator&() const {
	return TreeNodePtr<T>(*tree_, node_id_);
}

}
