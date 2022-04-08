#include "format.hpp"

#include "common/input_stream/input_stream.hpp"
#include "generator/automaton/is_accepted.hpp"
#include "generator/automaton/proxy.hpp"

#include <iostream>
#include <vector>

using namespace parsium;
using namespace parsium::common;

namespace character {

bool state_0_is_accepted(InputStream& is);
bool state_1_is_accepted(InputStream& is);

bool state_0_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		if(c >= 20 && c != '\"' && c != '\\') {
			is.advance();
			return state_1_is_accepted(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_1_is_accepted(InputStream&) {
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

bool state_0_is_accepted_when_halting(InputStream& is);
bool state_1_is_accepted_when_halting(InputStream& is);
bool state_2_is_accepted_when_halting(InputStream& is);
bool state_3_is_accepted_when_halting(InputStream& is);

bool state_0_is_accepted_when_halting(InputStream& is)
{
	if(!is.is_done()) {
		char c = is.peek();
		if(c == '\"'){
			is.advance();
			return state_1_is_accepted_when_halting(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_1_is_accepted_when_halting(InputStream& is)
{
	if(!is.is_done()) {
		// char c = is.peek();
		if(characters::is_accepted(is)) {
			return state_2_is_accepted_when_halting(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_2_is_accepted_when_halting(InputStream& is)
{
	if(!is.is_done()) {
		char c = is.peek();
		if(c == '\"') {
			is.advance();
			return state_3_is_accepted_when_halting(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_3_is_accepted_when_halting(InputStream& is)
{
	if(!is.is_done()) {
		return true;
	} else {
		return true;
	}
}

bool is_accepted_when_halting(InputStream& is)
{
	return state_0_is_accepted_when_halting(is);
}

}

void test_hand_generated() {
	using TestSet = std::vector<std::pair<std::string, bool>>;

	auto character_tests = TestSet{
		{"", false},
		{"a", true},
		{" ", true},
		{"\\", false},
		{"\"", false}};
	auto characters_tests = TestSet{
		{"", true},
		{"a", true},
		{" ", true},
		{"\\", true},
		{"\"", true},
		{"abc", true},
		{"\"abc", true},
		{"AZ", true},
		{"AZ\"abvcaXZ", true}};
	auto string_tests = TestSet{
		{R"()", false},
		{R"(")", false},
		{R"("")", true},
		{R"("abc")", true}};

	// Generated code tests.

	std::cout << "Character tests:" << std::endl;
	for(auto& test : character_tests ) {
		auto is = InputStream(test.first.c_str(), test.first.c_str() + test.first.size());
		if(character::is_accepted(is) != test.second) {
			std::cout << "  ko: " << test.first << std::endl;
		} else {
			std::cout << "  ok: " << test.first << std::endl;
		}
	}

	std::cout << "Characters tests:" << std::endl;
	for(auto& test : characters_tests ) {
		auto is = InputStream(test.first.c_str(), test.first.c_str() + test.first.size());
		if(characters::is_accepted(is) == test.second) {
			std::cout << "  ok: " << test.first << std::endl;
		} else {
			std::cout << "  ko: " << test.first << std::endl;
		}
	}

	std::cout << "String tests:" << std::endl;
	for(auto& test : string_tests ) {
		auto is = InputStream(test.first.c_str(), test.first.c_str() + test.first.size());
		if(string::is_accepted_when_halting(is) == test.second) {
			std::cout << "  ok: " << test.first << std::endl;
		} else {
			std::cout << "  ko: " << test.first << std::endl;
		}
	}
}

int main() {
	auto context = Context();
	auto json = json_format(context);
	auto is = InputStream("1");
	is_accepted(json.digits, is);
}
