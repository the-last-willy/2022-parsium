#pragma once

#include "parsium/mckeeman/builder/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
const Grammar& Rule::grammar() const {
	return *grammar_;
}

inline
Grammar& Rule::grammar() {
	return *grammar_;
}

}}}
