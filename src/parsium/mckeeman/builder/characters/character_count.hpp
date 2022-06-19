#pragma once

#include "parsium/mckeeman/builder/characters.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
std::size_t character_count(const Characters& cs) {
	return size(cs.content);
}

}}}
