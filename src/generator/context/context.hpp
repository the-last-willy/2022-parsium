#pragma once

#include "generator/automaton/automaton.hpp"
#include "generator/state/state.hpp"
#include "generator/transition/transition.hpp"

#include <vector>

namespace parsium {

struct Context {
	std::vector<Automaton> automata;
	std::vector<State> states;
	std::vector<Transition> transitions;

	const Automaton& ref(AutomatonId id) const {
		return automata[id.index];
	}

	Automaton& ref(AutomatonId id) {
		return automata[id.index];
	}

	const State& ref(StateId id) const {
		return states[id.index];
	}

	State& ref(StateId id) {
		return states[id.index];
	}

	const Transition& ref(TransitionId id) const {
		return transitions[id.index];
	}

	Transition& ref(TransitionId id) {
		return transitions[id.index];
	}
};

}
