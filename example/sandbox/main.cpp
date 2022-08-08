#include <parsium/mckeeman/formatting/raw.hpp>
#include <parsium/mckeeman/kickstarting/grammar.hpp>
#include <parsium/mckeeman/kickstarting/rules.hpp>
#include <parsium/mckeeman/storing/node.hpp>
#include <parsium/mckeeman/storing/validity.hpp>
#include <parsium/mckeeman/validating/validator.hpp>

#include <parsium/mckeeman/storing/validity.inl>

#include <iostream>

using namespace parsium;
using namespace parsium::mckeeman;

int main() {
	auto grammar_rules = std::vector<StorageNodeHandle>();
	for(auto rule : all_mckeeman_rules) {
		auto r = rule();
		assert(is_valid(*r));
		grammar_rules.push_back(std::move(r));
	}

	auto grammar = mckeeman_grammar_of(grammar_rules);
	assert(is_valid(*grammar));

	{
		auto f = RawFormatter();
		format(f, *grammar);
		std::cout << f.stream_.str() << std::endl;
	}

	auto v = Validator(*grammar);
//
//	for(auto rule : all_mckeeman_rules) {
//		auto r = rule();
//		assert(is_valid(*r));
//
//		{
//			auto f = RawFormatter();
//			format(f, *r);
//			std::cout << f.stream_.str() << std::endl;
//		}
//
//		auto s = std::span<const StorageNodeHandle>(&r, 1);
//		auto g = mckeeman_grammar_of(s);
//		assert(is_valid(*g));
//
//		{
//			auto f = RawFormatter();
//			format(f, *g);
//			std::cout << f.stream_.str() << std::endl;
//		}
//
//		std::cout << std::string(80, '=') << std::endl;
//	}

//	auto r = mckeeman_alternatives_rule();
//	assert(is_valid(*r));
//
//	{
//		auto f = RawFormatter();
//		format(f, *r);
//		std::cout << f.stream_.str() << std::endl;
//	}

//	auto g = mckeeman_rule_of(*r);
//	assert(is_valid(*g));
//
//	{
//		auto f = RawFormatter();
//		format(f, *g);
//		std::cout << f.stream_.str() << std::endl;
//	}
}
