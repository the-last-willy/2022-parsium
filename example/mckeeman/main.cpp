#include "format/json.hpp"

#include <parsium/common/tag/throw.hpp>
#include <parsium/mckeeman/formatting.hpp>
#include <parsium/mckeeman/parser.hpp>

#include <iostream>
#include <sstream>

using namespace parsium;
using namespace parsium::mckeeman;

std::string formatted(const builder::Grammar& g, const MultiHead& mh) {
	auto ss = std::stringstream();
	ss << "heads = {\n";
	for(auto& head : mh.heads) {
		ss << "  ";
		auto rule = mh.base_rule;
		for(auto& cursor : head.nested_cursors) {
			ss << name(*rule).string << "/";
			auto alternative_index = index_of_or(*rule, *cursor.alternative, _throw);
			ss << alternative_index << "/" << cursor.item_index << "/";
			auto& item = current_item(cursor);
			if(auto literal = literal_or(item, nullptr)) {
				ss << head.character_index;
			} else if(auto name = name_or(item, nullptr)) {
				rule = rule_or(g, *name, nullptr);
			} else {
				throw PreconditionViolation();
			}
		}
		ss << "\n";
	}
	ss << "}\n";
	return ss.str();
}

std::string formatted(const parser::Parser& p) {
	auto ss = std::stringstream();
	ss << "is_accepting = " << is_accepting(p) << ",\n";
	ss << formatted(p.grammar, p.multi_head);
	return ss.str();
}

int main() {
	auto format = format::json();

	std::cout << formatting::to_string(format) << std::endl;

	// auto json_parser = parser::parser(format, builder::Name("json"));
//	std::cout << format(json_parser) << std::endl;
//
//	std::cout << "> " << std::flush;
//	for(int c = std::getchar(); c != EOF; c = std::getchar()) {
//		if(c == '\n') {
//			continue;
//		}
//		feed(json_parser, char(c));
//		std::cout << format(json_parser) << std::endl;
//		std::cout << "> " << std::flush;
//	}
}

int main() {
	try {

	} catch(parsium::Exception) {

	} catch(...) {
		std::cerr << "Unhandled exception." << std::endl; 
	}
}
