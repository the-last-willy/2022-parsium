#pragma once

#include "parsium/mckeeman/storing/node.hpp"

namespace parsium::mckeeman {

template<typename F>
auto for_children(const StorageNode& n, F f) {
	if(has_child(n)) {
		auto c = child(n);
		while(1) {
			f(*c);
			if(has_sibling(*c)) {
				c = sibling(*c);
			} else {
				break;
			}
		}
	}
}

template<typename F>
auto for_siblings(const StorageNode& n, F f) {
	if(has_sibling(n)) {
		auto s = sibling(n);
		while(1) {
			f(*s);
			if(has_sibling(*s)) {
				s = sibling(*s);
			} else {
				break;
			}
		}
	}
}

auto child_with_name(const StorageNode& n, const char* name) -> NP<const StorageNode> {
	auto ret = NP<const StorageNode>();
	for_children(n, [&](const auto& c) {
		if(*mckeeman::name(c) == name) {
			ret = &c;
		}
	});
	return ret;
}

auto sibling_with_name(const StorageNode& n, const char* name) -> NP<const StorageNode> {
	auto ret = NP<const StorageNode>();
	for_siblings(n, [&](const auto& c) {
		if(*mckeeman::name(c) == name) {
			ret = &c;
		}
	});
	return ret;
}

}
