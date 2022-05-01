#include "format.hpp"

#include <iostream>

using namespace parsium::automaton;
using namespace parsium::common;

int main() {
	auto a = json_format_sign();
	print(a);

	auto test = "a+++";
	auto input = InputStream(test);
	auto b = fed_until_halt(*a.start_state, input);
	std::cout << test << " " << b.is_accepting << " " << input.content << std::endl;
}
