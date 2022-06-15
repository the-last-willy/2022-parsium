#pragma once

#include "parsium/mckeeman/parser/multi_head.hpp"

namespace parsium {
namespace mckeeman {

inline
bool is_accepting(const builder::Grammar& g, const builder::Rule& r) {
	if(r.does_accept_nothing()) {
		return true;
	} else {
		auto is_alternative_accepting = true;
		for(auto& alternative : alternatives(r)) {
			is_alternative_accepting = true;
			for(std::size_t i = 0; i < size(items(alternative)); ++i) {
				auto& item = items(alternative)[i];
				if(literal_or(item, nullptr)) {
					is_alternative_accepting = false;
					break;
				} else if(auto name = name_or(item, nullptr)) {
					if(!is_accepting(g, rule_or(g, *name, UB))) {
						is_alternative_accepting = false;
						break;
					}
				}
			}
			if(is_alternative_accepting) {
				break;
			}
		}
		return is_alternative_accepting;
	}
}

inline
bool is_accepting(const builder::Grammar& g, Head h) {
	auto result = true;
	while(!is_empty(h)) {
		auto& item = current_item(top_or(h, UB));
		if(literal_or(item, nullptr)) {
			result = false;
			break;
		} else if(auto name = name_or(item, nullptr)) {
			auto& rule = rule_or(g, *name, UB);
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
bool is_accepting(const builder::Grammar& g, const MultiHead& mh) {
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
