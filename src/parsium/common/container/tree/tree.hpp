#pragma once

#include "parsium/common/container/tree/internal/node.hpp"
#include "parsium/common/container/tree/internal/tree.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>
#include <parsium/common/typing/is_const.hpp>

#include <vector>

namespace parsium {

template<typename T>
class Tree {
	static_assert( !is_type_const<T> );

	TreeInternals<T> internals_;

public:
	// Access.

	auto root_or(decltype(nullptr)) const -> TreeNodePtr<const T> {
		return TreeNodePtr<const T>(internals_, internals_.root_id_);
	}

	auto root_or(decltype(nullptr)) -> TreeNodePtr<T> {
		return TreeNodePtr<T>(internals_, internals_.root_id_);
	}

	//

	auto construct_root_or(decltype(UB), const T& data) -> TreeNodeRef<T> {
		internals_.root_id_ = size(internals_.nodes_);
		internals_.nodes_.push_back(
			TreeNodeInternals<T>(invalid_tree_node_id, T(data)));
		return TreeNodeRef<T>(internals_, internals_.root_id_);
	}

	auto construct_root_or(decltype(UB), T&& data) -> TreeNodeRef<T> {
		internals_.root_id_ = size(internals_.nodes_);
		internals_.nodes_.push_back(
			TreeNodeInternals<T>(invalid_tree_node_id, std::move(data)));
		return TreeNodeRef<T>(internals_, internals_.root_id_);
	}

	auto destroy_root() -> void {
		internals_.nodes_.clear();
		internals_.root_id_ = invalid_tree_node_id;
	}
};

}
