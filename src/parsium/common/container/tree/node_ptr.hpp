#pragma once

#include "parsium/common/container/tree/internal/tree.hpp"
#include "parsium/common/container/tree/node_ref.hpp"

#include <parsium/common/typing/const_if.hpp>
#include <parsium/common/typing/is_const.hpp>
#include <parsium/common/typing/without_const.hpp>

namespace parsium {

/**
 * Lifetime is tied to `tree_`.
 */
template<typename T>
class TreeNodePtr {
	static constexpr auto is_const = is_type_const<T>;

	using MutableT = WithoutConst<T>;

	using QualifiedTreeInternals = ConstIf<TreeInternals<MutableT>, is_const>;

	QualifiedTreeInternals* tree_;
	std::size_t id_;

public:
	TreeNodePtr(QualifiedTreeInternals& t, std::size_t id)
	: tree_(&t)
	, id_(id)
	{}

	operator bool() const {
		return id_ != invalid_tree_node_id;
	}

	auto operator*() const -> TreeNodeRef<T> {
		return TreeNodeRef(*tree_, tree_->nodes_[id_]);
	}

	// auto operator->() const; ???
};

}
