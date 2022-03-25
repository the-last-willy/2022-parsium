#include "common/input_stream/input_stream.hpp"

#include <iostream>
#include <vector>

using namespace parsium;
using namespace parsium::common;

namespace character {

bool state_0_is_accepted(InputStream&is);
bool state_1_is_accepted(InputStream& is);

bool state_0_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		if(c >= 20 && c != '"' && c != '\\') {
			return state_1_is_accepted(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_1_is_accepted(InputStream& is) {
	return true;
}

bool is_accepted(InputStream& is) {
	return state_0_is_accepted(is);
}

} // namespace character

namespace characters {

bool state_0_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		if(character::is_accepted(is)) {
			return state_0_is_accepted(is);
		}
		return true;
	} else {
		return true;
	}
}

bool is_accepted(InputStream& is) {
	return state_0_is_accepted(is);
}

} // namespace characters

namespace string {



}

int main() {
	using TestSet = std::vector<std::pair<std::string, bool>>;

	auto character_tests = TestSet{
		{"a", true},
		{" ", true},
		{"\\", false},
		{"\"", false}};
	auto characters_tests = TestSet{
		{"a", true},
		{" ", true},
		{"\\", false},
		{"\"", false},
		{}};

	std::cout << "Character tests:" << std::endl;
	for(auto& test : character_tests ) {
		auto is = InputStream(test.first.c_str(), test.first.c_str() + test.first.size());
		if(character::is_accepted(is) != test.second) {
			std::cout << "  ko: " << test.first << std::endl;
		} else {
			std::cout << "  ok: " << test.first << std::endl;
		}
	}
}
