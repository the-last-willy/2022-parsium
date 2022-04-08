#pragma once

#include "automaton.hpp"
#include "proxy.hpp"

#include "generator/context/create_state_in_context.hpp"
#include "generator/state/proxy.hpp"
#include "generator/state/state.hpp"

namespace parsium {

inline
StateProxy create_state_in(AutomatonProxy automaton) {
	auto state = create_state_in(automaton.context());
	automaton->data.states.push_back(state);
	return state;
}

}
