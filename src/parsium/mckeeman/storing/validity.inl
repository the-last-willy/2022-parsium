#pragma once

#include "validity.hpp"

#include "parsium/mckeeman/storing/node.hpp"

#include "parsium/common/breakpoint.hpp"

namespace parsium::mckeeman {

//inline bool are_children_valid(const StorageNode& n) {
//	return false;
//}

//inline bool are_parents_valid(const StorageNode& n) {
//	return false;
//}

//inline bool are_siblings_valid(const StorageNode& n) {
//	return false;
//}

inline bool is_alternative_shallowly_valid(const StorageNode& n) {
	auto ret = true;
	// An alternative must have a child.
	ret = ret && breakpoint_on_false(has_child(n));
	// An alternative mustn't have a literal.
	ret = ret && breakpoint_on_false(!has_literal(n));
	// An alternative mustn't have a name.
	ret = ret && breakpoint_on_false(!has_name(n));
	return ret;
}

inline bool is_item_shallowly_valid(const StorageNode& n) {
	auto ret = true;
	if(is_literal(n)) {
		// A literal mustn't have a child.
		ret = ret && breakpoint_on_false(!has_child(n));
	}
	// There's no constraint for a name that's not a literal.
	return ret;
}

inline bool is_shallowly_valid(const StorageNode& n) {
	auto ret = true;
	if(is_alternative(n)) {
		ret = ret && is_alternative_shallowly_valid(n);
	} else if(is_item(n)) {
		ret = ret && is_item_shallowly_valid(n);
	} else {
		// Invalid node.
		ret = ret && breakpoint_on_false(false);
	}
	if(has_child(n)) {
		// Ensures that all children have `n` as a parent.
		for(auto c = child(n); has_sibling(*c); c = sibling(*c)) {
			auto b = has_parent(*c) && parent(*c) == &n;
			ret = ret && breakpoint_on_false(b);
		}
	}
	return ret;
}

inline bool is_valid(const StorageNode& n) {
	auto ret = is_shallowly_valid(n);
	if(has_child(n)) {
		// ret = ret && are_children_valid(n);
		ret = ret && is_valid(*child(n));
	}
	if(has_parent(n)) {
		// ret = ret && are_parents_valid(n);
	}
	if(has_sibling(n)) {
		// ret = ret && are_siblings_valid(n);
		ret = ret && is_valid(*sibling(n));
	}
	return ret;
}

}
