#pragma once

#include "parsium/mckeeman/builder/range_exclude.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
std::size_t character_count(const RangeExclude&) {
	return 1;
}

}}}
