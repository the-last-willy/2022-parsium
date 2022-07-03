#pragma once

#include "./multi_head.hpp"
#include "parsium/mckeeman/parser/multi_head_2.hpp"

#include <parsium/mckeeman/concept/grammar.hpp>
#include <parsium/mckeeman/concept/name.hpp>

#include <functional>
#include <vector>

namespace parsium {
namespace mckeeman {
namespace parser {

/**
 * \section Invariants
 * - `grammar_ != nullptr`
 */
class Parser {
	const builder::Grammar* grammar_;

public:
	MultiHead multi_head_;
	MultiHead2 multi_head_2_;

	explicit
	Parser(const builder::Rule& r)
	: grammar_(&mckeeman::grammar(r))
	{
		multi_head_ = multi_head(grammar(), r);

		auto root = multi_head_2_.tree_.construct_root(Cursor2());
		for(std::size_t i = 0; i < size(r.alternatives()); ++i) {
			auto& alternative = r.alternatives()[i];
			root->add_child(Cursor2({&alternative, 0}));
		}
	}

	auto grammar() const -> const builder::Grammar& {
		return *grammar_;
	}
};

inline
void feed2(Parser& p, char symbol) {

}

inline
void feed2(Parser& p, char symbol) {

}

}}}
