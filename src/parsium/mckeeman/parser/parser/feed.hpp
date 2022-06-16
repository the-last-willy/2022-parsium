#pragma once

#include "parser.hpp"
#include "parsium/mckeeman/parser/multi_head/fed.hpp"

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
			if(auto characters = characters_or(*literal, nullptr)) {
				if(characters->content[h.character_index] == symbol) {
					unify(result, moved_to_next_character(h));
				}
			} else if(auto range_exclude = range_exclude_or(*literal, nullptr)) {
				if(does_accept(*range_exclude, symbol)) {
					unify(result, moved_to_next_character(h));
				}
			} else if(auto singleton = singleton_or(*literal, nullptr)) {
				if(does_accept(*singleton, symbol)) {
					unify(result, moved_to_next_character(h));
				}
			}
		} else if(auto name = name_or(item, nullptr)) {
			auto& rule = mckeeman::rule_or(p.grammar, *name, UB);
			for(auto& alternative : alternatives(rule)) {
				auto nested = mckeeman::nested(h, alternative);
				unify(result, fed(p.grammar, nested, symbol));
			}
			if(is_accepting(p.grammar, rule)) {
				unify(result, fed(p.grammar, moved_to_next_item(h), symbol));
			}
		}
		return result;
	}
}

inline
MultiHead fed(parser::Parser& p, MultiHead& mh, char symbol) {
	auto result = MultiHead();
	for(auto& head : mh.heads) {
		unify(result, fed(p.grammar, head, symbol));
	}
	return result;
}

inline
void feed(parser::Parser& p, char symbol) {
	auto multi_head = MultiHead();
	multi_head.base_rule = p.multi_head.base_rule;
	unify(multi_head, fed(p.grammar, p.multi_head, symbol));
	p.multi_head = std::move(multi_head);
}

}}
