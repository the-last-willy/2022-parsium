#pragma once

#include "parsium/mckeeman/builder/item/builder.hpp"

#include <parsium/common/std/ranges/subrange/subrange.hpp>

#include <vector>

namespace parsium {
namespace mckeeman {

class RuleBuilder;

/**
 * \section Invariants
 * - `rule_ != nullptr`.
 */
class AlternativeBuilder {
	RuleBuilder* rule_;

	std::vector<ItemBuilder> items_;

public:
	explicit
	AlternativeBuilder(RuleBuilder& rule)
	: rule_(&rule)
	{}

	auto items() const {
		return subrange(begin(items_), end(items_));
	}

	auto items() {
		return subrange(begin(items_), end(items_));
	}

	const RuleBuilder& rule() const {
		return *rule_;
	}

	RuleBuilder& rule() {
		return *rule_;
	}

	//
};

}}
