#include <example/mckeeman/format/json.hpp>
#include <parsium/mckeeman/builder.hpp>
#include <parsium/mckeeman/parser.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string_view>

using namespace parsium;
using namespace parsium::mckeeman;

TEST_CASE("json") {
	SECTION("rule: \"json\"") {
		auto json = format::json();
		auto parser = parsium::mckeeman::parser::Parser(
			rule_or(*json, parsium::mckeeman::builder::Name("json"), _throw));
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
			auto input = std::string_view("{\"object\": {}, \"array\": [], \"string\": \"\", \"true\": true}");
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
		SECTION("#" + std::to_string(index++)) {
			auto input = std::string_view("[[[]]]");
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
			auto input = std::string_view("[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
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
			auto input = std::string_view("\"0123456789\"");
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
			auto input = std::string_view("\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"");
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
			auto input = std::string_view("\"abcdefghijklmnopqrstuvwxyz\"");
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
		SECTION("#"  + std::to_string(index++)) {
			auto input = std::string_view("1234567890");
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
			auto input = std::string_view("0.1234567890");
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
			auto input = std::string_view("true");
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
			auto input = std::string_view("false");
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
			auto input = std::string_view("null");
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
