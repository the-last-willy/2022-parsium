#include "test_sets.hpp"

#include <parsium/automaton.hpp>
#include <parsium/common.hpp>
#include <sandbox/json2/format.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iterator>

using namespace parsium::automaton;
using namespace parsium::common;

////////////////////////////////////////////////////////////////////////////////

void undergo(const Automaton& automaton, TestSet test_set) {
	SECTION(test_set.name) {
		for(std::size_t i = 0; i < size(test_set.tests); ++i) {
			SECTION("#" + std::to_string(i + 1) + ": `" + escaped(test_set.tests[i].input) + "`") {
				auto& test = test_set.tests[i];
				auto first = data(test.input);
				auto is = InputStream(std::string_view(first, first + size(test.input)));
				auto was_accepted = fed_until_halt(*automaton.start_state, is).is_accepting;
				REQUIRE(was_accepted == test.is_accepted);
				auto read_count = test.input.size() - is.content.size();
				REQUIRE(read_count == test.read_count);
			}
		}
	}
}

void test(const JSON_Format& json) {
//	undergo(json.character, character_test_set());
//	undergo(json.characters, characters_test_set());
//	undergo(json.digit, digit_test_set());
//	undergo(json.digits, digits_test_set());
//	undergo(json.integer, integer_test_set());
	undergo(json.onenine, onenine_test_set());
	undergo(json.sign, sign_test_set());
//	undergo(json.string, string_test_set());
//	undergo(json.value, value_test_set());
	undergo(json.ws, ws_test_set());
}

TEST_CASE("JSON generator") {
	auto json = json_format();
	test(json);
}
