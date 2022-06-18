#pragma once

#include <parsium/mckeeman/builder.hpp>

#include <memory>

namespace format {

using namespace parsium::mckeeman;

inline
std::unique_ptr<builder::Grammar> json() {
	auto result = std::make_unique<builder::Grammar>();
	auto& grammar =  *result;

	auto& json = grammar.add_rule("json");
	auto& value = grammar.add_rule("value");
	auto& object = grammar.add_rule("object");
	auto& members = grammar.add_rule("members");
	auto& member = grammar.add_rule("member");
	auto& array = grammar.add_rule("array");
	auto& elements = grammar.add_rule("elements");
	auto& element = grammar.add_rule("element");
	auto& string = grammar.add_rule("string");
	auto& characters = grammar.add_rule("characters");
	auto& character = grammar.add_rule("character");
	auto& escape = grammar.add_rule("escape");
	auto& hex = grammar.add_rule("hex");
	auto& number = grammar.add_rule("number");
	auto& integer = grammar.add_rule("integer");
	auto& digits = grammar.add_rule("digits");
	auto& digit = grammar.add_rule("digit");
	auto& onenine = grammar.add_rule("onenine");
	auto& fraction = grammar.add_rule("fraction");
	auto& exponent = grammar.add_rule("exponent");
	auto& sign = grammar.add_rule("sign");
	auto& ws = grammar.add_rule("ws");

	{
		auto& rule = json;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
		}
	} {
		auto& rule = value;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(object);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(array);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(string);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(number);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal("true"));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal("false"));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal("null"));
		}
	} {
		auto& rule = object;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('{'));
			alternative.add_item(ws);
			alternative.add_item(builder::literal('}'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('{'));
			alternative.add_item(members);
			alternative.add_item(builder::literal('}'));
		}
	} {
		auto& rule = members;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(member);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(member);
			alternative.add_item(builder::literal(','));
			alternative.add_item(members);
		}
	} {
		auto& rule = member;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(ws);
			alternative.add_item(string);
			alternative.add_item(ws);
			alternative.add_item(builder::literal(':'));
			alternative.add_item(element);
		}
	} {
		auto& rule = array;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('['));
			alternative.add_item(ws);
			alternative.add_item(builder::literal(']'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('['));
			alternative.add_item(elements);
			alternative.add_item(builder::literal(']'));
		}
	} {
		auto& rule = elements;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
			alternative.add_item(builder::literal(','));
			alternative.add_item(elements);
		}
	} {
		auto& rule = element;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(ws);
			alternative.add_item(value);
			alternative.add_item(ws);
		}
	} {
		auto& rule = string;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('"'));
			alternative.add_item(characters);
			alternative.add_item(builder::literal('"'));
		}
	} {
		auto& rule = characters;
		rule.add_alternative(builder::nothing);
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(character);
			alternative.add_item(characters);
		}
	} {
		auto& rule = character;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(literal(builder::range(' ', 127) - Singleton('"') - Singleton('\\')));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('\\'));
			alternative.add_item(escape);
		}
	} {
		auto& rule = escape;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('"'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('\\'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('/'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('b'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('f'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('n'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('r'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('t'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('u'));
			alternative.add_item(hex);
			alternative.add_item(hex);
			alternative.add_item(hex);
			alternative.add_item(hex);
		}
	} {
		auto& rule = hex;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(builder::range('A', 'F')));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(builder::range('a', 'f')));
		}
	} {
		auto& rule = number;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(integer);
			alternative.add_item(fraction);
			alternative.add_item(exponent);
		}
	} {
		auto& rule = integer;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(onenine);
			alternative.add_item(digits);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('-'));
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('-'));
			alternative.add_item(onenine);
			alternative.add_item(digits);
		}
	} {
		auto& rule = digits;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
			alternative.add_item(digits);
		}
	} {
		auto& rule = digit;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('0'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(onenine);
		}
	} {
		auto& rule = onenine;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(builder::range('1', '9')));
		}
	} {
		auto& rule = fraction;
		rule.add_alternative(builder::nothing);
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('.'));
			alternative.add_item(digits);
		}
	} {
		auto& rule = exponent;
		rule.add_alternative(builder::nothing);
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('E'));
			alternative.add_item(sign);
			alternative.add_item(digits);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('e'));
			alternative.add_item(sign);
			alternative.add_item(digits);
		}
	} {
		auto& rule = sign;
		rule.add_alternative(builder::nothing);
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('+'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal('-'));
		}
	} {
		auto& rule = ws;
		rule.add_alternative(builder::nothing);
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(char(0x20)));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(char(0x0A)));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(char(0x0D)));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(builder::literal(char(0x09)));
			alternative.add_item(ws);
		}
	}

	return result;
}

}