#pragma once

#include "parsium/mckeeman/builder/alternative.hpp"
#include "parsium/mckeeman/builder/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
const std::deque<Alternative>& Rule::alternatives() const {
	return alternatives_;
}

inline
std::deque<Alternative>& Rule::alternatives() {
	return alternatives_;
}

}}}
