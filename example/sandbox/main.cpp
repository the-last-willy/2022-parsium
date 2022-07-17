#include <parsium/formatting/tree.hpp>
#include <parsium/mckeeman_formatter.hpp>
#include <parsium/mckeeman_grammar.hpp>
#include <parsium/parsing_tree.hpp>

#include <iostream>

using namespace parsium;

int main() {
    auto instance = mckeeman_grammar();
    auto rule = mckeeman_rule_of(instance);

    auto f = TreeFormatter();
    format(f, instance);
    std::cout << "==INSTANCE==\n\n" << f.string_.str() << "\n\n" << std::flush;

	f = TreeFormatter();
	format(f, rule);
	std::cout << "==RULE==\n\n" << f.string_.str() << "\n\n" << std::flush;
}
