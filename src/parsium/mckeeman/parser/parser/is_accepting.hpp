#pragma once

#include "parser.hpp"
#include "parsium/mckeeman/parser/multi_head/is_accepting.hpp"

namespace parsium {
namespace mckeeman {

inline
bool is_accepting(const parser::Parser& p) {
	return is_accepting(p.grammar, p.multi_head);
}

}}
