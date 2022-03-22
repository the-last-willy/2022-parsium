#include <generated/fsm.hpp>

#include <iostream>
#include <string>

int main() {
	auto s = std::string();
	std::cout << "> ";
	while(std::cin >> s) {
		auto is = parsium::common::InputStream(data(s), data(s) + size(s));
		std::cout << "= " << dfsm::is_accepted(is) << std::endl;
		std::cout << "> ";
	}
}
