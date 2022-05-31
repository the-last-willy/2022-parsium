#include "json.hpp"

#include <parsium/mckeeman.hpp>

#include <iostream>

int main() {
	auto json_grammar = json_format();
	auto json_generator = parsium::mckeeman::Generator({&json_grammar});

	std::cout << generate_cpp(json_generator) << std::endl;
}
