#pragma once

#include "parsium/mckeeman.hpp"

parsium::mckeeman::Grammar json_format() {
	using namespace parsium::mckeeman;

	auto grammar =  parsium::mckeeman::Grammar();
	grammar.rules.reserve(22);

	auto& json = grammar.rules.emplace_back("json");
	auto& value = grammar.rules.emplace_back("value");
	auto& object = grammar.rules.emplace_back("object");
	auto& members = grammar.rules.emplace_back("members");
	auto& member = grammar.rules.emplace_back("member");
	auto& array = grammar.rules.emplace_back("array");
	auto& elements = grammar.rules.emplace_back("elements");
	auto& element = grammar.rules.emplace_back("element");
	auto& string = grammar.rules.emplace_back("string");
	auto& characters = grammar.rules.emplace_back("characters");
	auto& character = grammar.rules.emplace_back("character");
	auto& escape = grammar.rules.emplace_back("escape");
	auto& hex = grammar.rules.emplace_back("hex");
	auto& number = grammar.rules.emplace_back("number");
	auto& integer = grammar.rules.emplace_back("integer");
	auto& digits = grammar.rules.emplace_back("digits");
	auto& digit = grammar.rules.emplace_back("digit");
	auto& onenine = grammar.rules.emplace_back("onenine");
	auto& fraction = grammar.rules.emplace_back("fraction");
	auto& exponent = grammar.rules.emplace_back("exponent");
	auto& sign = grammar.rules.emplace_back("sign");
	auto& ws = grammar.rules.emplace_back("ws");

	{
		auto& rule = json;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(element);
		}
	} {
		auto& rule = value;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(object);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(array);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(string);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(number);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back("true");
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back("false");
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back("null");
		}
	} {
		auto& rule = object;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('{');
			alternative.items.emplace_back(ws);
			alternative.items.emplace_back('}');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('{');
			alternative.items.emplace_back(members);
			alternative.items.emplace_back('}');
		}
	} {
		auto& rule = members;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(member);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(member);
			alternative.items.emplace_back(',');
			alternative.items.emplace_back(members);
		}
	} {
		auto& rule = member;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(ws);
			alternative.items.emplace_back(string);
			alternative.items.emplace_back(ws);
			alternative.items.emplace_back(':');
			alternative.items.emplace_back(element);
		}
	} {
		auto& rule = array;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('[');
			alternative.items.emplace_back(ws);
			alternative.items.emplace_back(']');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('[');
			alternative.items.emplace_back(elements);
			alternative.items.emplace_back(']');
		}
	} {
		auto& rule = elements;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(element);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(element);
			alternative.items.emplace_back(',');
			alternative.items.emplace_back(elements);
		}
	} {
		auto& rule = element;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(ws);
			alternative.items.emplace_back(value);
			alternative.items.emplace_back(ws);
		}
	} {
		auto& rule = string;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('"');
			alternative.items.emplace_back(characters);
			alternative.items.emplace_back('"');
		}
	} {
		auto& rule = characters;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(character);
			alternative.items.emplace_back(characters);
		}
	} {
		auto& rule = character;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range(' ', 127) - exclude('"') - exclude('\\'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('\\');
			alternative.items.emplace_back(escape);
		}
	} {
		auto& rule = escape;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('"');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('\\');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('/');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('b');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('f');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('n');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('r');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('t');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('u');
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
		}
	} {
		auto& rule = hex;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('A', 'F'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('a', 'f'));
		}
	} {
		auto& rule = number;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(integer);
			alternative.items.emplace_back(fraction);
			alternative.items.emplace_back(exponent);
		}
	} {
		auto& rule = integer;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(onenine);
			alternative.items.emplace_back(digits);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('-');
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('-');
			alternative.items.emplace_back(onenine);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = digits;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = digit;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('0');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(onenine);
		}
	} {
		auto& rule = onenine;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('1', '9'));
		}
	} {
		auto& rule = fraction;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('.');
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = exponent;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('E');
			alternative.items.emplace_back(sign);
			alternative.items.emplace_back(digits);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('e');
			alternative.items.emplace_back(sign);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = sign;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('+');
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back('-');
		}
	} {
		auto& rule = ws;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(char(0x20));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(char(0x0A));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(char(0x0D));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(char(0x09));
			alternative.items.emplace_back(ws);
		}
	}
	
	return grammar;
}
