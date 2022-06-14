#pragma once

#include "parsium/mckeeman/builder/name.hpp"
#include "parsium/mckeeman/builder/rule.hpp"
#include "parsium/mckeeman/builder/traits.hpp"

#include <deque>
#include <string_view>

namespace parsium {
namespace mckeeman {
namespace builder {

class Grammar {
	std::deque<Rule> rules_;

public:
	using Traits = Traits;

	auto rules() const -> const std::deque<Rule>&;
	auto rules() -> std::deque<Rule>&;

	//

	Rule& add_rule(const Name& name) {
		return rules_.emplace_back(*this, name);
	}
};

}}}
