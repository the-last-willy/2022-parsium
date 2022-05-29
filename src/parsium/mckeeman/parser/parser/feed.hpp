#pragma once

#include "parser.hpp"
#include "parsium/mckeeman/parser/multi_head/fed.hpp"

namespace parsium {
namespace mckeeman {

inline
void feed(Parser& p, char symbol) {
	auto multi_head = MultiHead();
	multi_head.base_rule = p.multi_head.base_rule;
	unify(multi_head, fed(p.grammar, p.multi_head, symbol));
	p.multi_head = std::move(multi_head);
}

}}
