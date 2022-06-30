#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/node_id.hpp"

#include <parsium/common/tag/self.hpp>
#include <parsium/common/tag/undefined_behaviour.hpp>
#include <parsium/common/typing/const_if.hpp>
#include <parsium/common/typing/is_const.hpp>
#include <parsium/common/typing/without_const.hpp>

#include <span>

namespace parsium {

template<typename T>
class Tree;

/**
 * Pointer semantics.
 * Lifetime is tied to `tree_'.
 *
 * `TreeNode` encapsulates `TreeNodeData`.
 */
template<typename T>
class TreeNode {
public:
	static constexpr auto is_const = is_type_const<T>;

	using QualifiedIndex = ConstIf<TreeNodeIndex, is_const>;
	using QualifiedTree = ConstIf<Tree<WithoutConst<T>>, is_const>;

private:
	QualifiedTree* tree_;
	TreeNodeIndex index_;

public:
	TreeNode(QualifiedTree& qt, TreeNodeIndex i)
		: tree_(&qt)
		, index_(i)
	{
		// Node index validity not checked.
	}

	TreeNode(const TreeNode<WithoutConst<T>>& s)
		: tree_(&s.tree())
		, index_(s.index())
	{}

	auto children_indices() const -> std::span<QualifiedIndex>;
	auto index() const -> TreeNodeIndex;
	auto parent_index_or(decltype(self)) const -> TreeNodeIndex;
	auto tree() const -> QualifiedTree&;
};

template<typename T>
auto tree_node(const Tree<T>& t, TreeNodeIndex i) -> TreeNode<const T> {
	return TreeNode<const T>(t, i);
}

template<typename T>
auto tree_node(Tree<T>& t, TreeNodeIndex i) -> TreeNode<T> {
	return TreeNode<T>(t, i);
}

template<typename T>
auto parent_or(const TreeNode<T>& s, decltype(self)) -> TreeNode<T> {

}

}
