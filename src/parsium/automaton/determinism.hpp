#pragma once

#include "automaton.hpp"

#include <set>
#include <vector>

namespace parsium {
namespace automaton {

/**
 * @brief Checks if an automaton is deterministic.
 * @returns `true` if it is, `false` otherwise.
 */
inline
bool is_deterministic(const Automaton& a) {
	auto marked_states = std::set({a.start_state.get()});
	auto states_to_visit = std::vector({a.start_state.get()});

	while(not states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		for(std::size_t i = 0; i < current_state->transitions.size(); ++i) {
			auto& ti = current_state->transitions[i];
			for(std::size_t j = i + 1; j < current_state->transitions.size(); ++j) {
				auto& tj = current_state->transitions[j];
				if(ti.symbol == tj.symbol) {
					return false;
				}
			}

			if(not marked_states.contains(ti.end_state.get())) {
				marked_states.insert(ti.end_state.get());

				states_to_visit.push_back(ti.end_state.get());
			}
		}
	}

	return true;
}

}
}
