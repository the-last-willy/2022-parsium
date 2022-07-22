#pragma once

#include <parsium/common/breakpoint.hpp>

#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace parsium {

////////////////////////////////////////////////////////////////////////////////
// Declarations.

class MckeemanBackNode;
class MckeemanNode;

// Connectivity.

auto alternative(const MckeemanNode&, int index) -> const MckeemanNode*;
auto alternative(MckeemanNode&, int index) -> MckeemanNode*;
int alternative_count(const MckeemanNode&);
auto is_deterministic(const MckeemanNode&) -> bool;
auto next(const MckeemanNode&, int alternative_index) -> const MckeemanNode*;
auto next(MckeemanNode&, int alternative_index) -> MckeemanNode*;
auto parent(const MckeemanNode&) -> const MckeemanNode*;
auto parent(MckeemanNode&) -> MckeemanNode*;
auto previous(const MckeemanNode&) -> const MckeemanNode*;
auto previous(MckeemanNode&) -> MckeemanNode*;

// Extension.

auto create_alternative_at_end(MckeemanNode&) -> MckeemanNode*;
auto create_item_at_end(MckeemanNode&, int alternative_index) -> MckeemanNode*;
auto create_next_item(MckeemanNode&) -> MckeemanNode*;


// Literal.

auto has_literal(const MckeemanNode&) -> bool;
auto literal(const MckeemanNode&) -> const std::string*;
auto literal(MckeemanNode&) -> std::string*;

// Validity.

auto is_valid(const MckeemanNode&) -> bool;

auto is_shallowly_valid(const MckeemanNode&) -> bool;

////////////////////////////////////////////////////////////////////////////////
// Definitions.

class MckeemanNode {
public:
	std::string name_;

	// Either one or the other.

	std::vector<MckeemanNode> alternatives_;
	std::string literal_;

	// Connectivity.

	// Is owning if `*next_candidate_` is deterministic.
	MckeemanNode* next_candidate_ = nullptr;
	MckeemanNode* parent_ = nullptr;
	MckeemanNode* previous_ = nullptr;

	// Non-deterministic connectivity.

	std::shared_ptr<MckeemanBackNode> parent_next_ = nullptr;
};

class MckeemanBackNode {
public:
	std::optional<MckeemanNode> next_;
};

// Connectivity.

const MckeemanNode* alternative(const MckeemanNode& n, int index) {
	assert(index < alternative_count(n));
	return &n.alternatives_[index];
}

MckeemanNode* alternative(MckeemanNode& n, int index) {
	assert(index < alternative_count(n));
	return &n.alternatives_[index];
}

inline int alternative_count(const MckeemanNode& n) {
	return static_cast<int>(size(n.alternatives_));
}

inline bool is_deterministic(const MckeemanNode& n) {
	return alternative_count(n) <= 1;
}

const MckeemanNode* next(const MckeemanNode& n, int alternative_index) {
	auto nc = n.next_candidate_;
	if(!nc) {
		// No next.
		return nullptr;
	} else if(is_deterministic(*nc)) {
		// Single next possibility.
		return nc;
	} else {
		assert(false);
		// Multiple next possibilities.
		assert(alternative_index >= 0);
		assert(alternative_index < alternative_count(*nc));
		auto alternative = nc->alternatives_[alternative_index];
		return nullptr;
	}
}

MckeemanNode* next(MckeemanNode& n, int alternative_index) {
	auto nc = n.next_candidate_;
	if(!nc) {
		// No next.
		return nullptr;
	} else if(is_deterministic(*nc)) {
		// Single next possibility.
		return nc;
	} else {
		assert(false);
		// Multiple next possibilities.
		assert(alternative_index >= 0);
		assert(alternative_index < alternative_count(*nc));
		auto alternative = nc->alternatives_[alternative_index];
		return nullptr;
	}
}

const MckeemanNode* parent(const MckeemanNode& n) {
	return n.parent_;
}

MckeemanNode* parent(MckeemanNode& n) {
	return n.parent_;
}

const MckeemanNode* previous(const MckeemanNode& n) {
	return n.previous_;
}

MckeemanNode* previous(MckeemanNode& n) {
	return n.previous_;
}

// Extension.

MckeemanNode* create_alternative_at_end(MckeemanNode& n) {
	if(alternative_count(n) > 0) {
		assert(false); // Not implemented.
		return nullptr;
	} else {
		auto a = &n.alternatives_.emplace_back();
		a->parent_ = &n;
		return a;
	}
}

MckeemanNode* create_next_item(MckeemanNode& n) {
	assert(!n.next_candidate_);
	n.next_candidate_ = new MckeemanNode();
	n.next_candidate_->previous_ = &n;
	return n.next_candidate_;
}

// Literal.

auto has_literal(const MckeemanNode& n) -> bool {
	return !n.literal_.empty();
}

auto literal(const MckeemanNode& n) -> const std::string* {
	return &n.literal_;
}

auto literal(MckeemanNode& n) -> std::string* {
	return &n.literal_;
}

// Validity.

bool is_valid(const MckeemanNode& n) {
	auto ret = true;
	auto np = &n;
	while(true) {
		ret = ret && is_shallowly_valid(n);
		for(int i = 0; i < alternative_count(n); ++i) {
			auto a = alternative(n, i);
			ret = ret && (is_valid(*a));
		}
		if(alternative_count(*np) > 0) {
			np = alternative(*np, 0);
		} else {
			break;
		}
	}
	return ret;
}

bool is_shallowly_valid(const MckeemanNode& n) {
	auto ret = true;
	{
		// Doesn't have both alternatives and literal data.
		auto b = !((size(n.literal_) > 0) && (alternative_count(n) > 0));
		ret &= break_on_false(b);
	}
	for(int i = 0; i < alternative_count(n); ++i) {
		auto a = alternative(n, i);
		if(parent(*a) != &n) {
			breakpoint();
			ret = false;
		}
	}
	if(n.next_candidate_) {
		if(previous(*n.next_candidate_) != &n) {
			breakpoint();
			ret = false;
		}
	}
	if(auto p = previous(n)) {
		if(alternative(*p, 0) != &n) {
			breakpoint();
			ret = false;
		}
	}
	return ret;
}

}