#pragma once

#pragma once

#include "automaton.hpp"
#include "state.hpp"

#include <set>
#include <vector>

namespace parsium {
namespace automaton {

template<typename Callable>
void traverse_states(Automaton& a, Callable&& c) {
	auto marked_states = std::set({a.start_state.get()});
	auto states_to_visit = std::vector({a.start_state.get()});

	while(not states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		for(auto& transition : current_state->transitions) {
			if(not marked_states.contains(transition.end_state.get())) {
				marked_states.insert(transition.end_state.get());

				states_to_visit.push_back(transition.end_state.get());
			}
		}

		c(*current_state);
	}
}

}
}
