#pragma once

#include "parsium/common/container/naive_tree/node.hpp"

#include <optional>

namespace parsium::inline common::inline container {

/**
 * This is the most straightforward implementation of a tree you can make.
 *
 * Memory coherency is minimal (no coherency whatsoever).
 * Memory allocation is maximal (two allocations per node).
 * Memory fragmentation is maximal (two fragments per node).
 *
 * You can hardly write a worse implementation of a tree.
 * But you can hardly write a simpler one as well.
 *
 * One non trivial guarantee is the permanent validity of all references.
 *
 * \section Design
 *
 * - To write a better tree implementation would require underlying memory management patterns.
 * For example, a sparse set.
 *
 * - Whether to have a parent reference in a node or not is not obvious.
 * This has the nice side effects to be able to write algorithms iteratively with constant memory.
 *
 * \section Guarantees
 *
 * - References are invalidated only when the referenced node (or one of its parent) is deleted.
 *
 * \section TODO
 *
 * - Rewrite this container into something decent.
 *
 * - Separate data from nodes ?
 *
 * - Store the parent reference in the same container as the children references.
 * That way the tree could be traversed as a graph ?
 */
template<typename T>
class NaiveTree {
	std::optional<NaiveTreeNode<T>> root_;

public:
	using ConstNodePtr = const NaiveTreeNode<T>*;
	using MutableNodePtr = NaiveTreeNode<T>*;

	auto construct_root(T data) -> MutableNodePtr {
		return &root_.emplace(NaiveTreeNode<T>(nullptr, std::move(data)));
	}

	auto destroy_root() {
		root_.reset();
	}

	auto has_root() const -> bool {
		return root_.has_value();
	}

	auto root() const -> ConstNodePtr {
		return &root_.value();
	}

	auto root() -> MutableNodePtr {
		return &root_.value();
	}
};

}
