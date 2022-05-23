#include "json.hpp"

#include <parsium/mckeeman.hpp>

#include <iostream>
#include <sstream>

using namespace parsium;
using namespace parsium::mckeeman;

std::string format(const Grammar& g, const MultiHead& mh) {
	auto ss = std::stringstream();
	ss << "is_accepting = " << mh.is_accepting << ",\n";
	ss << "heads = {\n";
	for(auto& head : mh.heads) {
		ss << "  ";
		auto rule = mh.base_rule;
		for(auto& cursor : head.nested_cursors) {
			ss << rule->name.string << "/";
			auto alternative_index = alternative_index_or(*rule, *cursor.alternative, _throw);
			ss << alternative_index << "/" << cursor.item_index << "/";
			auto& item = current_item(cursor);
			if(auto literal = literal_or(item, nullptr)) {
				ss << cursor.character_index;
			} else if(auto name = name_or(item, nullptr)) {
				rule = &mckeeman::rule(g, *name);
			} else {
				throw PreconditionViolation();
			}
		}
		ss << "\n";
	}
	ss << "}\n";
	return ss.str();
}

std::string format(const Parser& p) {
	return format(p.grammar, p.multi_head);
}

int main() {
	auto json_parser = parser(json_format(), Name("element"));

	auto c = char();
	std::cout << "> ";
	while(std::cin >> c) {
		feed(json_parser, c);
		std::cout << format(json_parser) << std::endl;
		std::cout << "> ";
	}
}
