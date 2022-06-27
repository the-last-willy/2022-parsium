#pragma once

#include "parsium/common/container/tree/node.hpp"

#include <parsium/common/typing/const_if.hpp>

#include <vector>

namespace parsium {

class Tree;

/**
 * Subtrees have pointer semantics.
 * Lifetime is tied to `tree_` and `tree_`.
 */
template<typename T>
class Subtree {
public:
	using Tree = ConstIf<Tree, std::is_const_v<T>>;

private:
	Tree* tree_;

public:
	Subtree(Tree* t, Node* n)
};



}
