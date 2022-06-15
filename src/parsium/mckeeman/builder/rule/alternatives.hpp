#pragma once

#include "parsium/mckeeman/builder/alternative.hpp"
#include "parsium/mckeeman/builder/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
auto Rule::alternatives() const {
	return alternatives_;
}

inline
auto Rule::alternatives() {
	return alternatives_;
}

}}}
