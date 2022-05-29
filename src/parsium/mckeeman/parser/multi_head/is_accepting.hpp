#pragma once

#include "multi_head.hpp"

namespace parsium {
namespace mckeeman {

inline
bool is_accepting(const Grammar& g, Head h) {
	auto result = true;
	while(!is_empty(h)) {
		auto& item = current_item(top_or(h, UB));
		if(literal_or(item, nullptr)) {
			result = false;
			break;
		} else if(auto name = name_or(item, nullptr)) {
			auto& rule = mckeeman::rule(g, *name);
			if(is_accepting(g, rule)) {
				move_to_next_item(h);
			} else {
				result = false;
				break;
			}
		}
	}
	return result;
}

inline
bool is_accepting(const Grammar& g, const MultiHead& mh) {
	auto result = false;
	for(auto& head : mh.heads) {
		if(is_accepting(g, head)) {
			result = true;
			break;
		}
	}
	return result;
}

}}
