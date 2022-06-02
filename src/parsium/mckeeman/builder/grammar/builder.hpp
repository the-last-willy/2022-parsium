#pragma once

#include "parsium/mckeeman/builder/rule/builder.hpp"

#include <parsium/common/std/ranges/subrange/subrange.hpp>

#include <vector>

namespace parsium {
namespace mckeeman {

class GrammarBuilder {
	std::vector<RuleBuilder> rules_;

public:
	auto rules() const {
		return subrange(begin(rules_), end(rules_));
	}
};

}}
