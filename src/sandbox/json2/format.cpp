#include "format.hpp"

#include <array>

using namespace parsium::automaton;

JSON_Format json_format() {
	auto format = JSON_Format();
	
	format.array = json_format_array();
	format.character = json_format_character();
	format.characters = json_format_characters();
	format.digit = json_format_digit();
	format.digits = json_format_digits();
	format.element = json_format_element();
	format.elements = json_format_elements();
	format.escape = json_format_escape();
	format.exponent = json_format_exponent();
	format.fraction = json_format_fraction();
	format.hex = json_format_hex();
	format.integer = json_format_integer();
	format.json = json_format_json();
	format.member = json_format_member();
	format.members = json_format_members();
	format.number = json_format_number();
	format.object = json_format_object();
	format.onenine = json_format_onenine();
	format.sign = json_format_sign();
	format.string = json_format_string();
	format.value = json_format_value();
	format.ws = json_format_ws();

	return format;
}

Automaton json_format_array() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_character() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_characters() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_digit() {
	auto automaton = Automaton();

	auto state_0 = std::make_shared<State>(false);
	auto state_1 = std::make_shared<State>(true);

	state_0->transitions.emplace_back(transition(char('0'), state_1));
	state_0->transitions.emplace_back(transition(char('1'), state_1));
	state_0->transitions.emplace_back(transition(char('2'), state_1));
	state_0->transitions.emplace_back(transition(char('3'), state_1));
	state_0->transitions.emplace_back(transition(char('4'), state_1));
	state_0->transitions.emplace_back(transition(char('5'), state_1));
	state_0->transitions.emplace_back(transition(char('6'), state_1));
	state_0->transitions.emplace_back(transition(char('7'), state_1));
	state_0->transitions.emplace_back(transition(char('8'), state_1));
	state_0->transitions.emplace_back(transition(char('9'), state_1));

	return automaton;
}

Automaton json_format_digits() {
	auto automaton = Automaton();



	return automaton;
}

Automaton json_format_element() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_elements() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_escape() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_exponent() {
	auto automaton = Automaton();

	auto state_0 = std::make_shared<State>(true);
	auto state_1 = std::make_shared<State>(false);
	auto state_2 = std::make_shared<State>(false);
	auto state_3 = std::make_shared<State>(true);


	auto rule_0 =
	state_0->transitions.emplace_back(transition(char('e'), state_1));
	state_0->transitions.emplace_back(transition(char('E'), state_1));

	concatenate_with(*state_1, *json_format_sign().start_state);
	concatenate_with(*state_1, *json_format_digits().start_state);

	return automaton;
}

Automaton json_format_fraction() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_hex() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_integer() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_json() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_member() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_members() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_number() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_object() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_onenine() {
	auto rule = Automaton();
	rule.start_state = std::make_shared<State>(false);

	auto& state_0 = rule.start_state;
	auto state_1 = std::make_shared<State>(true);

	state_0->transitions.emplace_back(transition(char('1'), state_1));
	state_0->transitions.emplace_back(transition(char('2'), state_1));
	state_0->transitions.emplace_back(transition(char('3'), state_1));
	state_0->transitions.emplace_back(transition(char('4'), state_1));
	state_0->transitions.emplace_back(transition(char('5'), state_1));
	state_0->transitions.emplace_back(transition(char('6'), state_1));
	state_0->transitions.emplace_back(transition(char('7'), state_1));
	state_0->transitions.emplace_back(transition(char('8'), state_1));
	state_0->transitions.emplace_back(transition(char('9'), state_1));

	return rule;
}

Automaton json_format_sign() {
	auto rule = Automaton();
	rule.start_state = std::make_shared<State>(false);

	auto alternatives = std::array<Automaton, 3>();
	{
		alternatives[0].start_state = std::make_shared<State>(true);
	}
	{
		auto& state_0 = alternatives[1].start_state = std::make_shared<State>(false);
		auto state_1 = std::make_shared<State>(true);

		state_0->transitions.push_back(transition('+', state_1));
	}
	{
		auto& state_0 = alternatives[2].start_state = std::make_shared<State>(false);
		auto state_1 = std::make_shared<State>(true);

		state_0->transitions.push_back(transition('-', state_1));
	}

	for(auto& alternative : alternatives) {
		copy_transitions_from(*rule.start_state, *alternative.start_state);
		rule.start_state->is_accepting = rule.start_state->is_accepting
										 || alternative.start_state->is_accepting;
	}

	return rule;
}

Automaton json_format_string() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_value() {
	auto automaton = Automaton();


	return automaton;
}

Automaton json_format_ws() {
	auto rule = Automaton();
	rule.start_state = std::make_shared<State>(false);

	auto alternatives = std::array<Automaton, 5>();
	{
		alternatives[0].start_state = std::make_shared<State>(true);
	}
	{
		auto& state_0 = alternatives[1].start_state = std::make_shared<State>(false);

		state_0->transitions.push_back(transition(' ', rule.start_state));
	}
	{
		auto& state_0 = alternatives[2].start_state = std::make_shared<State>(false);

		state_0->transitions.push_back(transition('\n', rule.start_state));
	}
	{
		auto& state_0 = alternatives[3].start_state = std::make_shared<State>(false);

		state_0->transitions.push_back(transition('\r', rule.start_state));
	}
	{
		auto& state_0 = alternatives[4].start_state = std::make_shared<State>(false);

		state_0->transitions.push_back(transition('\t', rule.start_state));
	}

	for(auto& alternative : alternatives) {
		copy_transitions_from(*rule.start_state, *alternative.start_state);
		rule.start_state->is_accepting = rule.start_state->is_accepting
			|| alternative.start_state->is_accepting;
	}

	return rule;
}
