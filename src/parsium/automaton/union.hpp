#pragma once

#include "automaton.hpp"
#include "state.hpp"

#include <map>
#include <vector>

namespace parsium {
namespace automaton {

inline
std::shared_ptr<State> deterministic_union(const State& s0, const State& s1) {
	auto result = std::make_shared<State>(s0.is_accepting || s1.is_accepting);

	// Traverse all states of the intersection of s0 and s1.

	using BiState = std::pair<const State*, const State*>;

	auto states_to_visit = std::vector<BiState>({BiState(&s0, &s1)});
	auto registered_states = std::map<BiState, std::shared_ptr<State>>({{BiState(&s0, &s1), result}});

	while(!states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		auto current_unified_state = registered_states.find(current_state)->second;

		// Transitions for both s0 and s1.

		for(auto &t0: get<0>(current_state)->transitions)
			for(auto &t1: get<1>(current_state)->transitions) {
				if(t0.symbol == t1.symbol) {
					auto next_state = BiState(t0.end_state.get(),
						t1.end_state.get());
					auto it = registered_states.find(next_state);
					if(it != end(registered_states)) {
						auto &unified_transition = current_unified_state->transitions.emplace_back();
						unified_transition.symbol = t0.symbol;
						unified_transition.end_state = it->second;
					} else {
						auto &unified_transition = current_unified_state->transitions.emplace_back();
						unified_transition.symbol = t0.symbol;
						auto unified_state = std::make_shared<State>(
							get<0>(current_state)->is_accepting ||
							get<1>(current_state)->is_accepting);
						states_to_visit.push_back(current_state);
						registered_states[current_state] = unified_state;
						unified_transition.end_state = std::move(unified_state);
					}
					break;
				}
			}

		// Transitions for only s0.

		for(auto &t0: get<0>(current_state)->transitions) {
			auto found = false;
			for(auto &t1: get<1>(current_state)->transitions) {
				if(t1.symbol == t0.symbol) {
					found = true;
				}
			}
			if(!found) {
				auto& unified_state = registered_states[current_state];
				unified_state->transitions.push_back(t0);
			}
		}

		// Transitions for only s1.

		for(auto &t1: get<1>(current_state)->transitions) {
			auto found = false;
			for(auto &t0: get<0>(current_state)->transitions) {
				if(t0.symbol == t1.symbol) {
					found = true;
				}
			}
			if(!found) {
				auto& unified_state = registered_states[current_state];
				unified_state->transitions.push_back(t1);
			}
		}
	}

	//

	return result;
}

inline
Automaton deterministic_union(const Automaton& a0, const Automaton& a1) {
	auto result = Automaton();
	result.start_state = deterministic_union(*a0.start_state, *a1.start_state);
	return result;
}

}
}
