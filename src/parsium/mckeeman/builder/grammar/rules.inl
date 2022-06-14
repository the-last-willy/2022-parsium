#pragma once

#include "parsium/mckeeman/builder/grammar.hpp"
#include "parsium/mckeeman/builder/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

auto Grammar::rules() const -> const std::deque<Rule>& {
	return rules_;
}

auto Grammar::rules() -> std::deque<Rule>& {
	return rules_;
}

}}}
