#pragma once

#include "parsium/mckeeman/builder/rule/builder.hpp"

#include <parsium/common/std/ranges/subrange/subrange.hpp>

#include <list>
#include <string_view>

namespace parsium {
namespace mckeeman {

class GrammarBuilder {
	std::list<RuleBuilder> rules_;

public:
	auto rules() const {
		return subrange(begin(rules_), end(rules_));
	}

	//

	RuleBuilder& add_rule(const Name& )
};

}}
