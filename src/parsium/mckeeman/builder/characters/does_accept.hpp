#pragma once

#include "parsium/mckeeman/builder/characters.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
bool does_accept(const Characters& cs, std::size_t index, char c) {
	return cs.content[index] == c;
}

}}}
