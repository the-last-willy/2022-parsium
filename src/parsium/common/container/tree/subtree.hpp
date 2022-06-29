#pragma once

#include "parsium/common/container/tree/node.hpp"
#include "parsium/common/container/tree/node_index.hpp"

#include <parsium/common/typing/const_if.hpp>
#include <parsium/common/typing/without_const.hpp>

namespace parsium {

template<typename T>
class Tree;

template<typename T>
class SubtreeConnections {

public:

};

/**
 * Pointer semantics.
 * Lifetime is tied to `tree_'.
 */
template<typename T>
class Subtree {
public:
	using QualifiedTree = ConstIf<Tree<WithoutConst<T>>, std::is_const_v<T>>;

private:
	QualifiedTree* tree_;
	TreeNodeIndex node_;

public:
	Subtree(QualifiedTree& qt, TreeNodeIndex ni)
	: tree_(&qt)
	, node_(ni)
	{
		// Node index validity not checked.
	}

	Subtree(const Subtree<WithoutConst<T>>& s)
	: tree_(&s.tree())
	, node_(s.node())
	{}

	auto connections() const -> SubtreeConnections<T>;
	auto index() const -> TreeNodeIndex { return node_; }
	auto tree() const -> QualifiedTree&;
};

template<typename T>
auto subtree(const Tree<T>& t, TreeNodeIndex i) -> Subtree<const T> {
	return Subtree<const T>(t, i);
}

template<typename T>
auto subtree(Tree<T>& t, TreeNodeIndex i) -> Subtree<T> {
	return Subtree<T>(t, i);
}

template<typename T>
auto parent_or(const Subtree<T>& s, decltype(self)) -> Subtree<T> {

}

}
