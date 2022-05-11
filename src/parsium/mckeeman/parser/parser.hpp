#pragma once

#include "head.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct Parser {
	Grammar grammar;
	std::vector<Head> heads;
};

// Pseudo ctor.

inline
Parser parser(Grammar g, Name rule_name) {
	auto parser_ = Parser();
	parser_.grammar = std::move(g);
	auto& head = parser_.heads.emplace_back();
	auto& cursor = head.nested_cursors.emplace_back();
	cursor.rule = &rule(parser_.grammar, rule_name);
	return parser_;
}

// State.

inline
bool is_accepting(const Parser& p) {
	auto is_accepting_ = false;
	for(auto& h : p.heads) {
		if(is_empty(h)) {
			is_accepting_ = true;
			break;
		}
	}
	return is_accepting_;
}

inline
bool is_halted(const Parser& p) {
	return p.heads.empty();
}

// Feed.

inline
void feed(Parser& p, char symbol) {
	auto fed_heads = std::vector<Head>();
	for(auto& h : p.heads) {
		fed_heads = concatenation(std::move(fed_heads), fed(p.grammar, std::move(h), symbol));
	}
	p.heads = std::move(fed_heads);
}

}
}
