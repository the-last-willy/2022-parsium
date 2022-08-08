#pragma once

#include "validity.hpp"

#include "parsium/mckeeman/storing/iterating.hpp"
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
	// An alternative mustn't only have alternatives as children.
	for_children(n, [&](const auto& c) {
		ret = ret && breakpoint_on_false(!is_alternative(c));
	});
	// An alternative must only have alternatives as siblings.
	if(has_sibling(n)) {
		ret = ret && breakpoint_on_false(is_alternative(*sibling(n)));
	}
	return ret;
}

inline bool is_item_shallowly_valid(const StorageNode& n) {
	auto ret = true;
	if(is_literal(n)) {
		// A literal mustn't have a child.
		ret = ret && breakpoint_on_false(!has_child(n));
	}
	// There's no constraint for a name that's not a literal.
	// An item must only have items as siblings.
	if(has_sibling(n)) {
		ret = ret && breakpoint_on_false(is_item(*sibling(n)));
	}
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
			if(breakpoint_on_false(has_parent(*c))) {
				ret = ret && breakpoint_on_false(parent(*c) == &n);
			} else {
				ret = false;
			}
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
