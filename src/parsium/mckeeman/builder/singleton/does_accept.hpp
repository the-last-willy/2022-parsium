#pragma once

#include "parsium/mckeeman/builder/singleton.hpp"

#include <cstddef>

namespace parsium {
namespace mckeeman {
namespace builder {

inline
bool does_accept(const Singleton& s, std::size_t index, char c) {
	(void) index;
	return s.codepoint == c;
}

}}}
