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

struct Parser {
	builder::Grammar grammar;
	MultiHead multi_head;
//	ParserListener listener;
};

// Pseudo ctor.

inline
Parser parser(builder::Grammar g, const builder::Name& rule) {
	auto parser_ = Parser();
	parser_.grammar = std::move(g);
	parser_.multi_head = multi_head(parser_.grammar, *rule_or(parser_.grammar, rule, nullptr));
	return parser_;
}

}}}
