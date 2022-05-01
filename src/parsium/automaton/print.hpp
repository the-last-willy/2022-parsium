#pragma once

#include "automaton.hpp"

#include <iostream>
#include <map>
#include <vector>

namespace parsium {
namespace automaton {

inline
std::string escaped(char c) {
	auto result = std::string();
	switch(c) {
		case '\n': {
			result += "\\n";
		} break;
		case '\r': {
			result += "\\r";
		} break;
		case '\t': {
			result += "\\t";
		} break;
		case '\\': {
			result += "\\\\";
		} break;
		default: {
			result += c;
		}
	}
	return result;
}

inline
void print(const Automaton& a) {
	// States.

	std::cout << "States:" << std::endl;

	auto state_labels = std::map({std::pair{a.start_state.get(), std::size_t(0)}});
	auto states_to_visit = std::vector({a.start_state.get()});

	while(not states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		auto current_label = state_labels[current_state];

		std::cout << "  " << current_label << " = " << (current_state->is_accepting ? 'Y' : 'N') << " (" << std::hex << static_cast<int>(reinterpret_cast<intptr_t>(current_state)) << std::dec << ")" << std::endl;

		for(auto& t : current_state->transitions) {
			std::size_t next_label;
			auto it = state_labels.find(t.end_state.get());
			if(it != end(state_labels)) {
				next_label = it->second;
			} else {
				next_label = size(state_labels);
				state_labels[t.end_state.get()] = next_label;

				states_to_visit.push_back(t.end_state.get());
			}
		}
	}

	// Transitions.

	std::cout << "Transitions:" << std::endl;

	state_labels = std::map({std::pair{a.start_state.get(), std::size_t(0)}});
	states_to_visit = std::vector({a.start_state.get()});

	while(not states_to_visit.empty()) {
		auto current_state = states_to_visit.back();
		states_to_visit.pop_back();

		auto current_label = state_labels[current_state];

		for(auto& t : current_state->transitions) {
			std::size_t next_label;
			auto it = state_labels.find(t.end_state.get());
			if(it != end(state_labels)) {
				next_label = it->second;
			} else {
				next_label = size(state_labels);
				state_labels[t.end_state.get()] = next_label;

				states_to_visit.push_back(t.end_state.get());
			}

			std::cout << "  " << current_label << ", `" << escaped(t.symbol) << "` -> " << next_label << std::endl;
		}
	}
}

}
}
