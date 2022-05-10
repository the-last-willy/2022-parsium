#pragma once

#include "automaton.hpp"
#include "state.hpp"

#include <set>
#include <stdexcept>
#include <vector>

namespace parsium {
namespace automaton {

inline
void concatenate_with(State& s0, const State& s1) {
	// Traverse all states reachable from s0 once.

	auto states_to_visit = std::vector<State*>({&s0});
	auto visited_states = std::set<State*>({&s0});

	while(!states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		// Record all states directly reachable from the current state unless
		// they have already been visited.

		for(auto& transition : current_state->transitions) {
			if(!visited_states.contains(transition.end_state.get())) {
				visited_states.insert(transition.end_state.get());

				states_to_visit.push_back(transition.end_state.get());
			}
		}

		// An accepting state from s0 becomes a starting state to s1.

		if(current_state->is_accepting) {
			current_state->is_accepting = false;

			for(auto& transition : s1.transitions) {
				current_state->transitions.push_back(transition);
			}
		}
	}
}

}
}
