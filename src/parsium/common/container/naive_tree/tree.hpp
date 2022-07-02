#pragma once

#include "parsium/common/container/naive_tree/node.hpp"

#include <optional>

namespace parsium::inline common::inline container {

/**
 * This is the most straightforward implementation of a tree you can make.
 * Everything about it is terrible.
 * TODO .
 */
template<typename T>
class NaiveTree {
	std::optional<NaiveTreeNode<T>> root_;

public:
	auto construct_root(T data) -> NaiveTreeNode<T>& {
		return root_.emplace(NaiveTreeNode<T>(nullptr, std::move(data)));
	}

	auto destroy_root() {
		root_.reset();
	}

	auto has_root() const -> bool {
		return root_.has_value();
	}

	auto root() const -> const NaiveTreeNode<T>& {
		return root_.value();
	}

	auto root() -> NaiveTreeNode<T>& {
		return root_.value();
	}
};

}
