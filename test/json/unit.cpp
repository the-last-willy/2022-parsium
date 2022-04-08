#include "test_sets.hpp"

#include <common/input_stream/input_stream.hpp>
#include <generator/automaton/is_accepted.hpp>
#include <sandbox/json/format.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iterator>

using namespace parsium;

////////////////////////////////////////////////////////////////////////////////

void undergo(AutomatonProxy automaton, TestSet test_set) {
	SECTION(test_set.name) {
		for(std::size_t i = 0; i < size(test_set.tests); ++i) {
			SECTION("#" + std::to_string(i + 1) + ": `" + escaped(test_set.tests[i].input) + "`") {
				auto& test = test_set.tests[i];
				auto first = data(test.input);
				auto is = common::InputStream(first, first + size(test.input));
				auto was_accepted = is_accepted(automaton, is);
				REQUIRE(was_accepted == test.is_accepted);
				auto read_count = std::distance(static_cast<const char*>(first), is.first);
				REQUIRE(read_count == test.read_count);
			}
		}
	}
}

void test(const JSON_Format& json) {
	undergo(json.character, character_test_set());
	undergo(json.characters, characters_test_set());
	undergo(json.digit, digit_test_set());
	undergo(json.digits, digits_test_set());
	undergo(json.integer, integer_test_set());
	undergo(json.onenine, onenine_test_set());
	undergo(json.string, string_test_set());
	undergo(json.value, value_test_set());
	undergo(json.ws, ws_test_set());
}

TEST_CASE("JSON generator") {
	auto context = Context();
	auto json = json_format(context);
	test(json);
}
