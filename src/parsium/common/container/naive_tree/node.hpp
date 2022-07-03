#pragma once

#include <parsium/common/tag/undefined_behaviour.hpp>

#include <memory>
#include <vector>

namespace parsium::inline common::inline container {

template<typename T>
class NaiveTreeNode {
	NaiveTreeNode* parent_ = nullptr;
	std::vector<std::unique_ptr<NaiveTreeNode>> children_;

	T data_;

public:
	NaiveTreeNode(NaiveTreeNode* parent, T data)
	: parent_(parent)
	, data_(std::move(data))
	{}

	auto add_child(T data) -> NaiveTreeNode* {
		children_.push_back(std::unique_ptr<NaiveTreeNode>(
			new NaiveTreeNode(this, std::move(data))));
		return children_.back().get();
	}

	/**
	 * \pre `i < child_count()`
	 */
	auto child(std::size_t i) const -> const NaiveTreeNode* {
		return children_[i];
	}

	/**
	 * \pre `i < child_count()`
	 */
	auto child(std::size_t i) -> NaiveTreeNode* {
		return children_[i].get();
	}

	auto child_count() const -> std::size_t {
		return size(children_);
	}

	auto data() const -> const T* {
		return &data_;
	}

	auto data() -> T* {
		return &data_;
	}

	auto has_parent() const -> bool {
		return parent_ != nullptr;
	}

	/**
	 * \pre `has_parent()`
	 */
	auto parent() const -> const NaiveTreeNode* {
		return parent_;
	}

	/**
	 * \pre `has_parent()`
	 */
	auto parent() -> NaiveTreeNode* {
		return parent_;
	}

	/**
	 * \pre `i < child_count()`
	 * \todo Should be made iterative.
	 */
	auto remove_child(std::size_t i) -> void {
		children_.erase(begin(children_) + i);
	}
};

}
