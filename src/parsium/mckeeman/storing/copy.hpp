#pragma once

#include "parsium/mckeeman/storing/node.hpp"

#include <memory>

namespace parsium::mckeeman {

inline auto copy(const StorageNode& n, StorageNode* parent = nullptr) -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>(*name(n), *literal(n));
	ret->parent_ = parent;
	if(has_child(n)) {
		ret->child_ = copy(*child(n), ret.get());
	}
	if(has_sibling(n)) {
		ret->sibling_ = copy(*sibling(n), ret->parent_);
	}
	return ret;
}

}