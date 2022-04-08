#pragma once

#include "generator/automaton/automaton.hpp"
#include "generator/state/state.hpp"
#include "generator/unary_predicates.hpp"

#include <cstdlib>
#include <memory>

namespace parsium {

struct TransitionId {
	std::size_t index = 0;
};

struct TransitionData {
	StateId start_state;
	StateId end_state;

	bool use_condition = false;
	bool does_discard_symbol = true;
	std::unique_ptr<UnaryPredicate> condition;

	bool use_substate = false;
	AutomatonId substate;
};

struct Transition {
	TransitionId id;
	TransitionData data;
};

}