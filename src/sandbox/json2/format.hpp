#pragma once

#include <parsium/automaton.hpp>

#include <iostream>
#include <vector>

struct JSON_Format {
	parsium::automaton::Automaton json;
	parsium::automaton::Automaton value;
	parsium::automaton::Automaton object;
	parsium::automaton::Automaton members;
	parsium::automaton::Automaton member;
	parsium::automaton::Automaton array;
	parsium::automaton::Automaton elements;
	parsium::automaton::Automaton element;
	parsium::automaton::Automaton string;
	parsium::automaton::Automaton characters;
	parsium::automaton::Automaton character;
	parsium::automaton::Automaton escape;
	parsium::automaton::Automaton hex;
	parsium::automaton::Automaton number;
	parsium::automaton::Automaton integer;
	parsium::automaton::Automaton digits;
	parsium::automaton::Automaton digit;
	parsium::automaton::Automaton onenine;
	parsium::automaton::Automaton fraction;
	parsium::automaton::Automaton exponent;
	parsium::automaton::Automaton sign;
	parsium::automaton::Automaton ws;
};

JSON_Format json_format();

parsium::automaton::Automaton json_format_array();
parsium::automaton::Automaton json_format_character();
parsium::automaton::Automaton json_format_characters();
parsium::automaton::Automaton json_format_digit();
parsium::automaton::Automaton json_format_digits();
parsium::automaton::Automaton json_format_elements();
parsium::automaton::Automaton json_format_element();
parsium::automaton::Automaton json_format_escape();
parsium::automaton::Automaton json_format_exponent();
parsium::automaton::Automaton json_format_fraction();
parsium::automaton::Automaton json_format_hex();
parsium::automaton::Automaton json_format_integer();
parsium::automaton::Automaton json_format_json();
parsium::automaton::Automaton json_format_member();
parsium::automaton::Automaton json_format_members();
parsium::automaton::Automaton json_format_number();
parsium::automaton::Automaton json_format_object();
parsium::automaton::Automaton json_format_onenine();
parsium::automaton::Automaton json_format_sign();
parsium::automaton::Automaton json_format_string();
parsium::automaton::Automaton json_format_value();
parsium::automaton::Automaton json_format_ws();
