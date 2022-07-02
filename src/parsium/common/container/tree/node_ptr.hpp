#pragma once

#include "parsium/common/container/tree/internal/tree.hpp"
#include "parsium/common/container/tree/node_ref.hpp"

#include <parsium/common/typing/const_if.hpp>
#include <parsium/common/typing/is_const.hpp>
#include <parsium/common/typing/ptr/fake_ptr.hpp>
#include <parsium/common/typing/without_const.hpp>

namespace parsium {

template<typename T>
class TreeNodeRef;

/**
 * Lifetime is tied to `tree_`.
 */
template<typename T>
class TreeNodePtr {
	static constexpr auto is_const = is_type_const<T>;

	using MutableT = WithoutConst<T>;

	using QualifiedTreeInternals = ConstIf<TreeInternals<MutableT>, is_const>;

	QualifiedTreeInternals* tree_ = nullptr;
	std::size_t id_ = 0;

public:
	TreeNodePtr() = default;

	TreeNodePtr(decltype(nullptr)) : TreeNodePtr() {}

	TreeNodePtr(QualifiedTreeInternals& t, std::size_t id)
	: tree_(&t)
	, id_(id)
	{}

	operator bool() const {
		return tree_ && id_ != invalid_tree_node_id;
	}

	auto operator*() const -> TreeNodeRef<T>;
	auto operator->() const -> FakePtr<TreeNodeRef<T>>;
};

}
