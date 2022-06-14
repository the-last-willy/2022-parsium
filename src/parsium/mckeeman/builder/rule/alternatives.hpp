#pragma once

#include "parsium/mckeeman/builder/alternative.hpp"
#include "parsium/mckeeman/builder/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
auto Rule::alternatives() const {
	return subrange(begin(alternatives_), end(alternatives_));
}

inline
auto Rule::alternatives() {
	return subrange(begin(alternatives_), end(alternatives_));
}

}}}
