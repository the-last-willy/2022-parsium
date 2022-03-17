#pragma once

namespace at_least_one_b {

struct State {
	using transition_function_type = const State& (*)(char);

	bool accepting;
	transition_function_type transition_function;

	State() = default;

	constexpr
	State(transition_function_type fn, bool accepting)
		: accepting(accepting)
		, transition_function(fn)
	{}
};

const State& bin_state();
const State& bin_state_transition(char);
const State& state_0();
const State& state_0_transition(char);
const State& state_1();
const State& state_1_transition(char);

const State& bin_state() {
	static State s(&bin_state_transition, false);
	return s;
}

const State& bin_state_transition(char) {
	return bin_state();
}

const State& state_0() {
	static const State s(&state_0_transition, false);
	return s;
}

const State& state_0_transition(char c) {
	if(c == 'a') {
		return state_0();
	} else if(c == 'b') {
		return state_1();
	} else {
		return bin_state();
	}
}

const State& state_1() {
	static const State s(&state_1_transition, true);
	return s;
}

const State& state_1_transition(char c) {
	if(c == 'a') {
		return state_1();
	} else if(c == 'b') {
		return state_1();
	} else {
		return bin_state();
	}
}

}
