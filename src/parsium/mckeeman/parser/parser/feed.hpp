#pragma once

#include "parsium/mckeeman/parser/multi_head/fed.hpp"
#include "parsium/mckeeman/parser/parser.hpp"

namespace parsium {
namespace mckeeman {

inline
MultiHead fed(parser::Parser& p, const Head& h, char symbol) {
	if(h.nested_cursors.empty()) {
		return {};
	} else {
		auto result = MultiHead();
		auto& top = top_or(h, UB);
		auto& item = current_item(top);
		if(auto literal = literal_or(item, nullptr)) {
			if(does_accept(*literal, h.character_index, symbol)) {
				unify(result, moved_to_next_character(h));
			}
		} else if(auto name = name_or(item, nullptr)) {
			auto& rule = mckeeman::rule_or(p.grammar(), *name, UB);
			for(auto& alternative : alternatives(rule)) {
				auto nested = mckeeman::nested(h, alternative);
				unify(result, fed(p.grammar(), nested, symbol));
			}
			if(is_accepting(p.grammar(), rule)) {
				unify(result, fed(p.grammar(), moved_to_next_item(h), symbol));
			}
		}
		return result;
	}
}

inline
MultiHead fed(parser::Parser& p, MultiHead& mh, char symbol) {
	auto result = MultiHead();
	for(auto& head : mh.heads) {
		unify(result, fed(p.grammar(), head, symbol));
	}
	return result;
}

inline
void feed(parser::Parser& p, char symbol) {
	auto multi_head = MultiHead();
	multi_head.base_rule = p.multi_head_.base_rule;
	unify(multi_head, fed(p.grammar(), p.multi_head_, symbol));
	p.multi_head_ = std::move(multi_head);
}

}}
