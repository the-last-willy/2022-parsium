#pragma once

#include "parsium/mckeeman/parser/parser.hpp"

namespace parsium {
namespace mckeeman {

inline
bool is_halted(const parser::Parser& p) {
	return p.multi_head_.heads.empty();
}

}}
