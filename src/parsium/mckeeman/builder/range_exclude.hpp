#pragma once

#include <parsium/mckeeman/common/range.hpp>
#include <parsium/mckeeman/common/singleton.hpp>

#include <vector>

namespace parsium {
namespace mckeeman {
namespace builder {

struct RangeExclude {
	Range range;
	std::vector<Singleton> excludes;
};

inline
RangeExclude range_exclude(Range r) {
	return RangeExclude({r});
}

}}}
