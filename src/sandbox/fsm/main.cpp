#include <iostream>

#include "example/at_least_one_b.hpp"
#include "example/even_number_of_a.hpp"

int main() {
	auto input = std::string();
	while(std::cin >> input) {
		const even_number_of_a::State* s = &even_number_of_a::state_0();
		for(auto c : input) {
			s = &s->transition_function(c);
		}
		std::cout << s->accepting << std::endl;
	}
}
