#include "json.hpp"

#include <parsium/mckeeman.hpp>

#include <iostream>
#include <sstream>

using namespace parsium::mckeeman;

std::string format(const Head& h) {
	auto format_ = std::stringstream() << ".";
	if(!is_empty(h)) {
		for(auto& cursor : h.nested_cursors) {
			format_ << "/" << cursor.rule->name.string;
			format_ << "/" << cursor.alternative;
			format_ << "/" << cursor.item;
			format_ << "/" << cursor.character;
		}
	}
	return format_.str();
}

void print(const Parser& p) {
	std::cout << "is_accepting = " << (is_accepting(p) ? "true" : "false") << "\n";
	std::cout << "is_halted    = " << (is_halted(p) ? "true" : "false") << "\n";
	std::cout << "heads[" << size(p.heads) << "] = {\n";
	for(auto& h : p.heads) {
		(void) h;
		std::cout << "  \"" << format(h) << "\"\n";
	}
	std::cout << "}\n";
}

int main() {
	auto json_parser = parser(json_format(), Name("number"));

	print(json_parser);
	std::cout << std::endl;

	feed(json_parser, '1');

	print(json_parser);
	std::cout << std::endl;

	feed(json_parser, '2');

	print(json_parser);
	std::cout << std::endl;

	feed(json_parser, '3');

	print(json_parser);
	std::cout << std::endl;
}
