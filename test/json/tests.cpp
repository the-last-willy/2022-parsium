#include <example/mckeeman/json.hpp>
#include <parsium/mckeeman.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string_view>

TEST_CASE("json") {
	SECTION("rule: \"json\"") {
		auto parser = parsium::mckeeman::parser(
			json_format(), parsium::mckeeman::Name("json"));
		auto index = 1;
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("{}");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("[]");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#"  + std::to_string(index++)) {
			auto input = std::string_view("\"\"");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#"  + std::to_string(index++)) {
			auto input = std::string_view("0");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("\"true\"");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("\"false\"");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("\"null\"");
			auto i = std::size_t(0);
			for(; i < size(input); ++i) {
				feed(parser, input[i]);
				if(is_halted(parser)) {
					break;
				}
			}
			REQUIRE(is_accepting(parser));
			REQUIRE(i == size(input));
		}
	}
}
