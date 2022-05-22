#pragma once

#include "multi_head.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct Parser {
	Grammar grammar;
	MultiHead multi_head;
};

// Pseudo ctor.

inline
Parser parser(Grammar g, Name rule_name) {
	auto parser_ = Parser();
	parser_.grammar = std::move(g);
	parser_.multi_head = multi_head(parser_.grammar, rule(parser_.grammar, rule_name));
	return parser_;
}

// State.

inline
bool is_accepting(const Parser& p) {
	return p.multi_head.is_accepting;
}

inline
bool is_halted(const Parser& p) {
	return p.multi_head.heads.empty();
}

}
}
