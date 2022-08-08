#pragma once

#include "parsium/common/breakpoint.hpp"
#include "parsium/common/pointer.hpp"

#include <cassert>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

namespace parsium::mckeeman {

class StorageNode {
public:
	std::string name_;
	std::string literal_;

	std::unique_ptr<StorageNode> child_;
	std::unique_ptr<StorageNode> sibling_;
	StorageNode* parent_ = nullptr;

	explicit StorageNode(std::string name = "", std::string literal = "")
	: name_(std::move(name))
	, literal_(std::move(literal))
	{}
};

using StorageNodeHandle = std::unique_ptr<StorageNode>;

bool has_child(const StorageNode& n) {
	return n.child_ != nullptr;
}

const StorageNode* child(const StorageNode& n) {
	return n.child_.get();
}

StorageNode* child(StorageNode& n) {
	return n.child_.get();
}

bool has_sibling(const StorageNode& n) {
	return n.sibling_ != nullptr;
}

const StorageNode* sibling(const StorageNode& n) {
	return n.sibling_.get();
}

StorageNode* sibling(StorageNode& n) {
	return n.sibling_.get();
}

bool has_parent(const StorageNode& n) {
	return n.parent_ != nullptr;
}

const StorageNode* parent(const StorageNode& n) {
	return n.parent_;
}

StorageNode* parent(StorageNode& n) {
	return n.parent_;
}

bool has_literal(const StorageNode& n) {
	return !n.literal_.empty();
}

const std::string* literal(const StorageNode& n) {
	return &n.literal_;
}

std::string* literal(StorageNode& n) {
	return &n.literal_;
}

bool has_name(const StorageNode& n) {
	return !n.name_.empty();
}

const std::string* name(const StorageNode& n) {
	return &n.name_;
}

std::string* name(StorageNode& n) {
	return &n.name_;
}

bool is_name(const StorageNode& n) {
	return has_name(n);
}

bool is_literal(const StorageNode& n) {
	return has_literal(n);
}

bool is_item(const StorageNode& n) {
	return is_literal(n) || is_name(n);
}

bool is_alternative(const StorageNode& n) {
	return !is_item(n);
}

StorageNode* add_child(StorageNode& n, std::unique_ptr<StorageNode>&& child) {
	assert(child != nullptr);
	assert(n.child_ == nullptr);
	n.child_ = std::move(child);
	n.child_->parent_ = &n;
	if(has_sibling(*n.child_)) {
		auto it = sibling(*n.child_);
		while(true) {
			it->parent_ = &n;
			if(has_sibling(*it)) {
				it = sibling(*it);
			} else {
				break;
			}
		}
	}
	return n.child_.get();
}

StorageNode* add_sibling(StorageNode& n, std::unique_ptr<StorageNode>&& item) {
	assert(n.sibling_ == nullptr);
	n.sibling_ = std::move(item);
	n.sibling_->parent_ = n.parent_;
	return n.sibling_.get();
}

auto link_as_alternatives(std::vector<std::unique_ptr<StorageNode>> nodes) -> std::unique_ptr<StorageNode> {
	auto ret = std::unique_ptr<StorageNode>();
	auto i = std::size_t(0);
	for(; i < size(nodes); ++i) {
		auto& node = nodes[i];
		if(node != nullptr) {
			ret = std::make_unique<StorageNode>();
			add_child(*ret, std::move(node));
			break;
		}
	}
	auto it = ret.get();
	for(; i < size(nodes); ++i) {
		auto& node = nodes[i];
		if(node != nullptr) {
			ret = std::make_unique<StorageNode>();
			add_child(*ret, std::move(node));
			it = add_sibling(*it, std::move(node));
		}
	}
	return ret;
}

auto link_as_siblings(std::vector<std::unique_ptr<StorageNode>> nodes) -> std::unique_ptr<StorageNode> {
	auto ret = std::unique_ptr<StorageNode>();
	auto i = std::size_t(0);
	for(; i < size(nodes); ++i) {
		auto& node = nodes[i];
		if(node != nullptr) {
			ret = std::move(node);
			break;
		}
	}
	auto it = ret.get();
	for(; i < size(nodes); ++i) {
		auto& node = nodes[i];
		if(node != nullptr) {
			it = add_sibling(*it, std::move(node));
		}
	}
	return ret;
}

}
