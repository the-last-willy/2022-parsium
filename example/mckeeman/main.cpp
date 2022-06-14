#include "format/json.hpp"

#include <parsium/mckeeman/parser.hpp>

#include <iostream>
#include <sstream>

using namespace parsium;
using namespace parsium::mckeeman;
//
//std::string format(const Grammar& g, const MultiHead& mh) {
//	auto ss = std::stringstream();
//	ss << "heads = {\n";
//	for(auto& head : mh.heads) {
//		ss << "  ";
//		auto rule = mh.base_rule;
//		for(auto& cursor : head.nested_cursors) {
//			ss << rule->name.string << "/";
//			auto alternative_index = alternative_index_or(*rule, *cursor.alternative, _throw);
//			ss << alternative_index << "/" << cursor.item_index << "/";
//			auto& item = current_item(cursor);
//			if(auto literal = literal_or(item, nullptr)) {
//				ss << head.character_index;
//			} else if(auto name = name_or(item, nullptr)) {
//				rule = &mckeeman::rule(g, *name);
//			} else {
//				throw PreconditionViolation();
//			}
//		}
//		ss << "\n";
//	}
//	ss << "}\n";
//	return ss.str();
//}
//
//std::string format(const Parser& p) {
//	auto ss = std::stringstream();
//	ss << "is_accepting = " << is_accepting(p) << ",\n";
//	ss << format(p.grammar, p.multi_head);
//	return ss.str();
//}

int main() {
	auto format = format::json();

	auto json_parser = parser::parser(format, builder::Name("json"));
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
