#pragma once

#include "grammar.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct ParserPosition {
	const Rule* rule;
	std::size_t alternative_index = 0;
	std::size_t item_index = 0;
	std::size_t character_index = 0;
};

enum struct ParserState {
	halted,
	waiting,
};

struct Parser {
	ParserState state = ParserState::waiting;

	const Rule* top_rule = nullptr;

	std::vector<ParserPosition> position_stack;
};

inline
std::vector<ParserPosition> find_accepting(const Grammar& g, const Rule& r, char c) {
	auto stack = std::vector<ParserPosition>();
	while(not stack.empty()) {
		auto position = &stack.front();
		auto& rule = *position->rule;
		auto& alternative = rule.alternatives[position->alternative_index];
		auto& first_item = alternative.items.front();
		if(auto literal = std::get_if<Literal>(&first_item.content)) {
			if(does_accept(*literal, c)) {
				break;
			}
		} else if(auto name = std::get_if<Name>(&first_item.content)) {
			auto& nested_position = stack.emplace_back();
			nested_position.rule = &mckeeman::rule(g, *name);
			continue;
		}
		position->alternative_index += 1;
		if(position->alternative_index == size(rule.alternatives)) {

		}
	}
	return stack;
}

inline
bool feed(Parser& p, char character) {
	if(p.state == ParserState::halted) {
		return false;
	} else if(p.state == ParserState::waiting) {
		if(p.position_stack.empty()) {
			auto& position = p.position_stack.emplace_back();
			auto& top_rule = position.rule = p.top_rule;
			auto alternative_i = std::size_t(0);
			for(; alternative_i < size(top_rule->alternatives); ++alternative_i) {
				auto& alternative = position.rule->alternatives[alternative_i];
				auto& first_item = alternative.items.front();
				if(auto literal = std::get_if<Literal>(&first_item.content)) {
					if(auto c = std::get_if<char>(&literal->content)) {
						if(*c == character) {
							position.alternative_index = alternative_i;
							break;
						}
					} else if(auto re = std::get_if<std::pair<Range, Exclude>>(&literal->content)) {
						auto& [range, exclude] = *re;
						if(does_accept(range, character) and does_accept(exclude, character)) {
							position.alternative_index = alternative_i;
							break;
						}
					} else if(auto s = std::get_if<std::string>(&literal->content)) {
						if(size(*s) > 0 and s->front() == character) {
							position.alternative_index = alternative_i;
							break;
						}
					}
				} else if(auto name = std::get_if<Name>(&first_item.content)) {
					position.alternative_index = alternative_i;
				}
			}
			if(alternative_i == size(top_rule->alternatives)) {
				p.state = ParserState::halted;
				return false;
			}
		}
	}
}

}
}
