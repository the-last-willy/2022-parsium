#pragma once

#include "parsium/mckeeman/builder/alternative/builder.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace parsium {
namespace mckeeman {

class GrammarBuilder;

/**
 * \section Invariants
 * - `grammar_ != nullptr`.
 */
class RuleBuilder {
	GrammarBuilder* grammar_;

	std::string name_;

	std::vector<AlternativeBuilder> alternatives_;

public:
	RuleBuilder(GrammarBuilder& grammar, std::string_view name)
	: grammar_(&grammar)
	, name_(name)
	{}

	const GrammarBuilder& grammar() const {
		return *grammar_;
	}

	GrammarBuilder& grammar() {
		return *grammar_;
	}

	std::string_view name() const {
		return name_;
	}
};

}}
