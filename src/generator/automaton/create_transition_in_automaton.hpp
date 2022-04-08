#pragma once

#include "proxy.hpp"

#include "generator/context/create_transition_in_context.hpp"
#include "generator/transition/proxy.hpp"

namespace parsium {

inline
TransitionProxy create_transition_in(AutomatonProxy automaton) {
	auto transition = create_transition_in(automaton.context());
	// automaton->data.transition.push_back(state);
	return transition;
}

}
