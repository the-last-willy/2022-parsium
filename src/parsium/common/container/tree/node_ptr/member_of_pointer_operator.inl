#pragma once

#include "parsium/common/container/tree/node_ptr.hpp"
#include "parsium/common/container/tree/node_ref.hpp"

namespace parsium {

template<typename T>
FakePtr<TreeNodeRef<T>> TreeNodePtr<T>::operator->() const {
	return FakePtr<TreeNodeRef<T>>(TreeNodeRef<T>(*tree_, id_));
}

}
