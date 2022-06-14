#pragma once

#include "parsium/mckeeman/builder/alternative.hpp"
#include "parsium/mckeeman/builder/alternative/nothing.hpp"
#include "parsium/mckeeman/builder/name.hpp"
#include "parsium/mckeeman/builder/traits.hpp"

#include <parsium/common/std/ranges/subrange/subrange.hpp>

#include <list>
#include <string>
#include <string_view>

namespace parsium {
namespace mckeeman {
namespace builder {

class Grammar;

/**
 * \section Invariants
 * - `grammar_ != nullptr`.
 */
class Rule {
	Grammar* grammar_;

	Name name_;

	std::list<Alternative> alternatives_;
	bool does_accept_nothing_ = false;

public:
	using Traits = Traits;

	Rule(Grammar& grammar, Name n)
	: grammar_(&grammar)
	, name_(std::move(n))
	{}

	auto alternatives() const;
	auto alternatives();
	auto grammar() const -> const Grammar&;
	auto grammar() -> Grammar&;

	const Name& name() const {
		return name_;
	}

	//

	void add_alternative(Nothing) {
		does_accept_nothing_ = true;
	}

	Alternative& add_alternative() {
		return alternatives_.emplace_back(*this);
	}

	//

	operator const Name&() const {
		return name_;
	}
};

}}}
