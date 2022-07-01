#pragma once

#include "parsium/common/container/tree/internal/node.hpp"
#include "parsium/common/container/tree/internal/tree.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>
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
	std::size_t node_id_;

public:
	TreeNodeRef(QualifiedTreeInternals& t, std::size_t node_id)
	: tree_(&t)
	, node_(&t.nodes_[node_id])
	, node_id_(node_id)
	{}

	auto operator&() const -> TreeNodePtr<T>;

	auto child_count() const -> std::size_t;
	auto child_or(decltype(UB), std::size_t i) const -> TreeNodeRef<T>;
	auto data() const -> T&;
	auto parent_or(decltype(nullptr)) const -> TreeNodePtr<T>;

	auto add_child(T t) const -> TreeNodeRef<T> {
		auto child_id = size(tree_->nodes_);
		tree_->nodes_.push_back(TreeNodeInternals<T>(node_id_, std::move(t)));
		return TreeNodeRef<T>(*tree_, child_id);
	}
};

}
