#pragma once

#include <generator/automaton/proxy.hpp>
#include <generator/context/context.hpp>

#include <iostream>
#include <vector>

struct JSON_Format {
	parsium::AutomatonProxy json;
	parsium::AutomatonProxy value;
	parsium::AutomatonProxy object;
	parsium::AutomatonProxy members;
	parsium::AutomatonProxy member;
	parsium::AutomatonProxy array;
	parsium::AutomatonProxy elements;
	parsium::AutomatonProxy element;
	parsium::AutomatonProxy string;
	parsium::AutomatonProxy characters;
	parsium::AutomatonProxy character;
	parsium::AutomatonProxy escape;
	parsium::AutomatonProxy hex;
	parsium::AutomatonProxy number;
	parsium::AutomatonProxy integer;
	parsium::AutomatonProxy digits;
	parsium::AutomatonProxy digit;
	parsium::AutomatonProxy onenine;
	parsium::AutomatonProxy fraction;
	parsium::AutomatonProxy exponent;
	parsium::AutomatonProxy sign;
	parsium::AutomatonProxy ws;
};

JSON_Format json_format(parsium::Context& context);

void initialize_array(JSON_Format&);
void initialize_character(JSON_Format&);
void initialize_characters(JSON_Format&);
void initialize_digit(JSON_Format&);
void initialize_digits(JSON_Format&);
void initialize_elements(JSON_Format&);
void initialize_element(JSON_Format&);
void initialize_escape(JSON_Format&);
void initialize_exponent(JSON_Format&);
void initialize_fraction(JSON_Format&);
void initialize_hex(JSON_Format&);
void initialize_integer(JSON_Format&);
void initialize_json(JSON_Format&);
void initialize_member(JSON_Format&);
void initialize_members(JSON_Format&);
void initialize_number(JSON_Format&);
void initialize_object(JSON_Format&);
void initialize_onenine(JSON_Format&);
void initialize_sign(JSON_Format&);
void initialize_string(JSON_Format&);
void initialize_value(JSON_Format&);
void initialize_ws(JSON_Format&);
