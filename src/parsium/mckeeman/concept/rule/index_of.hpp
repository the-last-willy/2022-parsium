#pragma once

#include "parsium/mckeeman/concept/alternative.hpp"
#include "parsium/mckeeman/concept/rule.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
#include <parsium/common/tag/throw.hpp>

#include <cstddef>

namespace parsium {
namespace mckeeman {

inline
std::size_t index_of_or(const Rule_ auto& r, const Alternative_ auto& a, decltype(_throw)) {
	auto result = std::size_t(0);
	for(; result < size(alternatives(r)); ++result) {
		if(&alternatives(r)[result] == &a) {
			break;
		}
	}
	if(result < size(alternatives(r))) {
		return result;
	} else {
		throw PreconditionViolation();
	}
}

}}
