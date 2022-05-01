#pragma once

#include "state.hpp"

namespace parsium {
namespace automaton {

inline
void copy_transitions_from(State& to, const State& from) {
	for(auto& transition : from.transitions) {
		to.transitions.push_back(transition);
	}
}

}
}