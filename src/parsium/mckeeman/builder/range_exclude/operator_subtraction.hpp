#pragma once

#include "parsium/mckeeman/builder/range_exclude.hpp"

#include <parsium/mckeeman/common/range.hpp>
#include <parsium/mckeeman/common/singleton.hpp>

namespace parsium {
namespace mckeeman {
namespace builder {

inline
RangeExclude operator-(Range r, Singleton s) {
	auto result = range_exclude(r);
	result.excludes.push_back(s);
	return result;
}

inline
RangeExclude operator-(RangeExclude re, Singleton s) {
	re.excludes.push_back(s);
	return re;
}

}}}
