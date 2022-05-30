#pragma once

#include "parsium/mckeeman/parser/message/message.hpp"
#include "parsium/mckeeman/parser/multi_head/multi_head.hpp"

#include <functional>
#include <vector>

namespace parsium {
namespace mckeeman {

using ParserListener = std::function<void(ParserMessage)>;

struct Parser {
	Grammar grammar;
	MultiHead multi_head;
	ParserListener listener;
};

// Pseudo ctor.

inline
Parser parser(Grammar g, const Name& rule_name) {
	auto parser_ = Parser();
	parser_.grammar = std::move(g);
	parser_.multi_head = multi_head(parser_.grammar, rule(parser_.grammar, rule_name));
	return parser_;
}

}
}
