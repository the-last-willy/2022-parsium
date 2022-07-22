#include <parsium/formatting/tree.hpp>
#include <parsium/mckeeman_formatter.hpp>
#include <parsium/mckeeman_grammar.hpp>
#include <parsium/mckeeman_node.hpp>
#include <parsium/parsing_tree.hpp>

#include <iostream>

using namespace parsium;

int main() {
	auto n = MckeemanNode();
	assert(is_valid(n));
	auto a0 = create_alternative_at_end(n);
	assert(is_valid(n));

	create_next_item(n);
	assert(is_valid(n));

//	std::cout << &n << " " << next(n, 0) << std::endl;

	auto f = TreeFormatter();
	format(f, n);
	std::cout << f.string_.str() << std::endl;
}
