#pragma once

#include "parser.hpp"

namespace parsium {
namespace mckeeman {

inline
bool is_halted(const Parser& p) {
	return p.multi_head.heads.empty();
}

}}
