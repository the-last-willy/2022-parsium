#pragma once

#include "parsium/mckeeman/builder/range_exclude.hpp"

/**
 * `does_accept` is not specific to this submodule.
 * It should be implemented in the common module.
 */

namespace parsium {
namespace mckeeman {
namespace builder {

inline
bool does_accept(const RangeExclude& re, char c) {
	if(does_accept(re.range, c)) {
		auto result = true;
		for(auto e : re.excludes) {
			if(c == e) {
				result = false;
				break;
			}
		}
		return result;
	} else {
		return false;
	}
}

}}}
