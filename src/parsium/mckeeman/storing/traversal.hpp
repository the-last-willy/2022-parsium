#pragma once

#include "parsium/mckeeman/storing/node.hpp"

#include <concepts>

namespace parsium::mckeeman {

inline void traverse_siblings_only(const StorageNode& n, std::predicate<const StorageNode&> auto p) {
	if(p(n) && has_sibling(n)) {
		return traverse_siblings_only(*sibling(n), std::move(p));
	}
}

}
