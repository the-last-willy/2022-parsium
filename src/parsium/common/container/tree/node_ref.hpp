#pragma once

#include "parsium/common/container/tree/internal/node.hpp"
#include "parsium/common/container/tree/internal/tree.hpp"

#include <parsium/common/typing/const_if.hpp>
#include <parsium/common/typing/is_const.hpp>
#include <parsium/common/typing/without_const.hpp>

namespace parsium {

template<typename T>
class TreeNodePtr;

/**
 * Lifetime is tied to `tree_`.
 */
template<typename T>
class TreeNodeRef {
	static constexpr auto is_const = is_type_const<T>;

	using MutableT = WithoutConst<T>;

	using QualifiedNodeInternals = ConstIf<TreeNodeInternals<MutableT>, is_const>;
	using QualifiedTreeInternals = ConstIf<TreeInternals<MutableT>, is_const>;

	QualifiedTreeInternals* tree_;
	QualifiedNodeInternals* node_;

public:
	TreeNodeRef(QualifiedTreeInternals& t, QualifiedNodeInternals& n)
	: tree_(&t)
	, node_(&n)
	{}

	auto parent_or(decltype(nullptr)) const -> TreeNodePtr<T>;
};

}
