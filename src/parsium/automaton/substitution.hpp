#pragma once

#include "automaton.hpp"
#include "state.hpp"
#include "traversal.hpp"

namespace parsium {
namespace automaton {

inline
void substitute(Automaton& a, const State& before, const std::shared_ptr<State>& after) {
	traverse_states(a, [&](State& s) {
		for(auto& transition : s.transitions) {
			if(transition.end_state.get() == &before) {
				transition.end_state = after;
			}
		}
	});
}

}
}