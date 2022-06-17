#pragma once

#include "./multi_head.hpp"

#include <parsium/mckeeman/concept/grammar.hpp>
#include <parsium/mckeeman/concept/name.hpp>

#include <functional>
#include <vector>

namespace parsium {
namespace mckeeman {
namespace parser {

// using ParserListener = std::function<void(ParserMessage)>;

/**
 * \section Invariants
 * - `grammar_ != nullptr`
 */
class Parser {
	const builder::Grammar* grammar_;

public:
	MultiHead multi_head_;

	explicit
	Parser(const builder::Rule& r)
	: grammar_(&mckeeman::grammar(r))
	{
		multi_head_ = multi_head(grammar(), r);
	}

	auto grammar() const -> const builder::Grammar& {
		return *grammar_;
	}
};

}}}
