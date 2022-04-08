#include "format.hpp"

#include "generator/automaton/proxy.hpp"
#include "generator/automaton/create_state_in_automaton.hpp"
#include "generator/automaton/create_transition_in_automaton.hpp"
#include "generator/context/create_automaton_in_context.hpp"
#include "generator/unary_predicates.hpp"

using namespace parsium;

JSON_Format json_format(
	Context& context)
{
	auto format = JSON_Format();
	
	format.array = create_automaton_in(context);
	format.character = create_automaton_in(context);
	format.characters = create_automaton_in(context);
	format.digit = create_automaton_in(context);
	format.digits = create_automaton_in(context);
	format.element = create_automaton_in(context);
	format.elements = create_automaton_in(context);
	format.escape = create_automaton_in(context);
	format.exponent = create_automaton_in(context);
	format.fraction = create_automaton_in(context);
	format.hex = create_automaton_in(context);
	format.integer = create_automaton_in(context);
	format.json = create_automaton_in(context);
	format.member = create_automaton_in(context);
	format.members = create_automaton_in(context);
	format.number = create_automaton_in(context);
	format.object = create_automaton_in(context);
	format.onenine = create_automaton_in(context);
	format.sign = create_automaton_in(context);
	format.string = create_automaton_in(context);
	format.value = create_automaton_in(context);
	format.ws = create_automaton_in(context);
	
	initialize_array(format);
	initialize_character(format);
	initialize_characters(format);
	initialize_digit(format);
	initialize_digits(format);
	initialize_element(format);
	initialize_elements(format);
	initialize_escape(format);
	initialize_exponent(format);
	initialize_fraction(format);
	initialize_hex(format);
	initialize_integer(format);
	initialize_json(format);
	initialize_member(format);
	initialize_members(format);
	initialize_number(format);
	initialize_object(format);
	initialize_onenine(format);
	initialize_sign(format);
	initialize_string(format);
	initialize_value(format);
	initialize_ws(format);

	return format;
}

void initialize_array(
    JSON_Format& format)
{
	(void)format;
}

void initialize_character(
    JSON_Format& format)
{
	auto automaton = format.character;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	automaton->data.start_state = state_0;
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<AndUnaryPredicate>(
			std::make_unique<RangeUnaryPredicate>(char(20), char(127)),
			std::make_unique<AndUnaryPredicate>(
				std::make_unique<NotUnaryPredicate>(std::make_unique<EqualUnaryPredicate>('\"')),
				std::make_unique<NotUnaryPredicate>(std::make_unique<EqualUnaryPredicate>('\\'))));
	}
}

void initialize_characters(
    JSON_Format& format)
{
	auto automaton = format.characters;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = true;

	automaton->data.start_state = state_0;
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_0;
		transition->data.use_substate = true;
		transition->data.substate = format.character;
	}
}

void initialize_digit(
    JSON_Format& format)
{
	auto automaton = format.digit;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	automaton->data.start_state = state_0;

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<EqualUnaryPredicate>('0');
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.onenine;
	}
}

void initialize_digits(
    JSON_Format& format)
{
	auto automaton = format.digits;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	automaton->data.start_state = state_0;

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.digit;
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_1;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.digits;
	}
}

void initialize_element(
    JSON_Format& format)
{
	(void)format;
}

void initialize_elements(
    JSON_Format& format)
{
    (void)format;
}

void initialize_escape(
    JSON_Format& format)
{
    (void)format;
}

void initialize_exponent(
    JSON_Format& format)
{
    (void)format;
}

void initialize_fraction(
    JSON_Format& format)
{
    (void)format;
}

void initialize_hex(
    JSON_Format& format)
{
    (void)format;
}

void initialize_integer(
    JSON_Format& format)
{
	auto automaton = format.integer;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = false;

	auto state_2 = create_state_in(automaton);
	state_2->data.is_final = true;

	auto state_3 = create_state_in(automaton);
	state_3->data.is_final = true;

	auto state_4 = create_state_in(automaton);
	state_4->data.is_final = false;

	auto state_5 = create_state_in(automaton);
	state_5->data.is_final = false;

	auto state_6 = create_state_in(automaton);
	state_6->data.is_final = true;

	auto state_7 = create_state_in(automaton);
	state_7->data.is_final = true;

	automaton->data.start_state = state_0;

	// The order of declaration of transitions matters.
	// This is non-compliant with the McKeeman Form.
	// `onenine digits` must be tried before `digit`
	// except `digit` is introduced first in the format.
	// The order here is therefore reversed.

	// `onenine digits`

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.onenine;
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_1;
		transition->data.end_state = state_2;
		transition->data.use_substate = true;
		transition->data.substate = format.digits;
	}

	// `digit`

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_3;
		transition->data.use_substate = true;
		transition->data.substate = format.digit;
	}

	// The hyphen has to be done independently of the two next rules
	// because both rules depend on it.
	// Support for non-determinism is required.

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_4;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<EqualUnaryPredicate>('-');
	}

	// The order is also reversed here.

	// `'-' onenine digits`

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_4;
		transition->data.end_state = state_5;
		transition->data.use_substate = true;
		transition->data.substate = format.onenine;
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_5;
		transition->data.end_state = state_6;
		transition->data.use_substate = true;
		transition->data.substate = format.digits;
	}

	// `'-' digit`

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_4;
		transition->data.end_state = state_7;
		transition->data.use_substate = true;
		transition->data.substate = format.digit;
	}
}

void initialize_json(
    JSON_Format& format)
{
    (void)format;
}

void initialize_member(
    JSON_Format& format)
{
    (void)format;
}

void initialize_members(
    JSON_Format& format)
{
    (void)format;
}

void initialize_number(
    JSON_Format& format)
{
    auto automaton = format.number;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = false;

	auto state_2 = create_state_in(automaton);
	state_2->data.is_final = false;

	auto state_3 = create_state_in(automaton);
	state_3->data.is_final = false;

	automaton->data.start_state = state_0;

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.integer;
	}
	{
		// ...
	}
	{
		// ...
	}
}

void initialize_object(
    JSON_Format& format)
{
    (void)format;
}

void initialize_onenine(
    JSON_Format& format)
{
	auto automaton = format.onenine;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	automaton->data.start_state = state_0;

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<RangeUnaryPredicate>('1', '9');
	}
}

void initialize_sign(
    JSON_Format& format)
{
    (void)format;
}

void initialize_string(
    JSON_Format& format)
{
	auto automaton = format.string;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = false;

	auto state_2 = create_state_in(automaton);
	state_2->data.is_final = false;

	auto state_3 = create_state_in(automaton);
	state_3->data.is_final = true;

	automaton->data.start_state = state_0;
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<EqualUnaryPredicate>('\"');
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_1;
		transition->data.end_state = state_2;
		transition->data.use_substate = true;
		transition->data.substate = format.characters;
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_2;
		transition->data.end_state = state_3;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<EqualUnaryPredicate>('\"');
	}
}

void initialize_value(
    JSON_Format& format)
{
    auto automaton = format.value;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = false;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	// All value types are disjoint luckily.
	// But having it unchecked like so is pretty bad.
	// Need support for non-determinism and then determinization.

	{
		// Object.
	}
	{
		// Array.
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.string;
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_substate = true;
		transition->data.substate = format.number;
	}
	{
		// "true".
	}
	{
		// "false".
	}
	{
		// "null".
	}
}

void initialize_ws(
    JSON_Format& format)
{
	auto automaton = format.ws;

	auto state_0 = create_state_in(automaton);
	state_0->data.is_final = true;

	auto state_1 = create_state_in(automaton);
	state_1->data.is_final = true;

	automaton->data.start_state = state_0;

	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_0;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<InUnaryPredicate>(std::vector<char>{' ', '\n', '\r', '\t'});
	}
	{
		auto transition = create_transition_in(automaton);
		transition->data.start_state = state_1;
		transition->data.end_state = state_1;
		transition->data.use_condition = true;
		transition->data.condition = std::make_unique<InUnaryPredicate>(std::vector<char>{' ', '\n', '\r', '\t'});
	}
}

