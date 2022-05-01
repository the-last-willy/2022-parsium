#pragma once

#include "automaton.hpp"
#include "state.hpp"

#include <set>
#include <stdexcept>
#include <vector>

namespace parsium {
namespace automaton {

inline
State composed_with(State s0, std::shared_ptr<State> s1) {
	if(not s1) {
		throw std::logic_error("Nullptr.");
	}

	// Accepting states.
	{
		auto states_to_visit = std::vector<std::shared_ptr<State>>({s1});
		auto visited_states = std::set<std::shared_ptr<State>>();

		while(!states_to_visit.empty()) {
			auto current_state = states_to_visit.back();
			states_to_visit.pop_back();

			if(current_state->is_accepting) {
				if(not current_state->transitions.empty()) {
					current_state->is_accepting = false;
				}

				for(auto& composition_transition : s0.transitions) {
					for(auto& current_transition : current_state->transitions) {
						if(current_transition.symbol == composition_transition.symbol) {
							throw std::logic_error("Non-deterministic automaton not handled.");
						}
					}

					current_state->transitions.push_back(composition_transition);
				}
			}

			for(auto& transition : current_state->transitions) {
				if(not visited_states.contains(transition.end_state)) {
					visited_states.insert(transition.end_state);

					states_to_visit.push_back(transition.end_state);
				}
			}
		}
	}

	// Start state.
	{
		s0.transitions = std::move(s1->transitions);
	}

	return s0;
}

}
}
