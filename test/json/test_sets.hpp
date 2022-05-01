#pragma once

#include <string>
#include <tuple>
#include <vector>

std::string escaped(std::string str) {
	auto escaped = std::string();
	for(auto c : str) {
		switch(c) {
			case '\n': {
				escaped += "\\n";
			} break;
			case '\r': {
				escaped += "\\r";
			} break;
			case '\t': {
				escaped += "\\t";
			} break;
			case '\\': {
				escaped += "\\\\";
			} break;
			default: {
				escaped += c;
			}
		}
	}
	return escaped;
}

////////////////////////////////////////////////////////////////////////////////

struct Test {
	std::string input;
	bool is_accepted;
	int read_count = -1;
};

struct TestSet {
	std::string name;
	std::vector<Test> tests;
};

////////////////////////////////////////////////////////////////////////////////

TestSet character_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/character";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "a",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = " ",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "\"",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "\\",
			.is_accepted = false,
			.read_count = 0}};
	return test_set;

}

TestSet characters_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/characters";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "a",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = " ",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "abc",
			.is_accepted = true,
			.read_count = 3},
		Test{
			.input = "\"",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "\\",
			.is_accepted = true,
			.read_count = 0}};
	return test_set;
}

TestSet digit_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/digit";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = " ",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "/",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "0",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "1",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "2",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "3",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "4",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "5",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "6",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "7",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "8",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "9",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "a",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "z",
			.is_accepted = false,
			.read_count = 0}};
	return test_set;
}

TestSet digits_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/digits";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = " ",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "0",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "00",
			.is_accepted = true,
			.read_count = 2},
		Test{
			.input = "0123456789",
			.is_accepted = true,
			.read_count = 10},
		Test{
			.input = "1",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "123456789",
			.is_accepted = true,
			.read_count = 9},
		Test{
			.input = "a",
			.is_accepted = false,
			.read_count = 0}};
	return test_set;
}

TestSet integer_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/integer";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "-",
			.is_accepted = false,
			.read_count = 1},
		Test{
			.input = "-0",
			.is_accepted = true,
			.read_count = 2},
		Test{
			.input = "-1234567890",
			.is_accepted = true,
			.read_count = 11},
		Test{
			.input = "0",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "00",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "01",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "1234567890",
			.is_accepted = true,
			.read_count = 10},};
	return test_set;
}

TestSet onenine_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/onenine";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = " ",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "/",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "0",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "1",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "2",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "3",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "4",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "5",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "6",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "7",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "8",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "9",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "a",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "z",
			.is_accepted = false,
			.read_count = 0}};
	return test_set;
}

TestSet sign_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/sign";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "a",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "+",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "-",
			.is_accepted = true,
			.read_count = 1}};
	return test_set;
}

TestSet string_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/string";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "\"",
			.is_accepted = false,
			.read_count = 1},
		Test{
			.input = "\"\"",
			.is_accepted = true,
			.read_count = 2},
		Test{
			.input = "\"abc\"",
			.is_accepted = true,
			.read_count = 5},
		Test{
			.input = "\"abc",
			.is_accepted = false,
			.read_count = 4}};
	return test_set;
}

TestSet value_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/value";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = false,
			.read_count = 0},
		Test{
			.input = "\"string\"",
			.is_accepted = true,
			.read_count = 8},
		Test{
			.input = "01234567890",
			.is_accepted = true,
			.read_count = 10}};
	return test_set;
}

TestSet ws_test_set() {
	auto test_set = TestSet();
	test_set.name = "JSON/ws";
	test_set.tests = std::vector<Test>{
		Test{
			.input = "",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = " ",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "0",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "a",
			.is_accepted = true,
			.read_count = 0},
		Test{
			.input = "\n",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "\n\n",
			.is_accepted = true,
			.read_count = 2},
		Test{
			.input = "\r",
			.is_accepted = true,
			.read_count = 1},
		Test{
			.input = "\t",
			.is_accepted = true,
			.read_count = 1}};
	return test_set;
}
