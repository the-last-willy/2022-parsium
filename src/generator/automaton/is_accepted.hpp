#pragma once

#include "proxy.hpp"

#include "generator/transition/is_accepting.hpp"

#include <common/input_stream/input_stream.hpp>

namespace parsium {

inline
bool is_accepted(AutomatonProxy ap, common::InputStream& is) {
	auto& automaton = ap.automaton();
	auto& context = ap.context();

	auto current_state = &context.ref(automaton.data.start_state);

	while(!is.is_done()) {
		bool found = false;
		for(auto& transition : context.transitions) {
			if(transition.id.index == 4) {
				is.is_done();
			}
			if(transition.data.start_state == current_state->id) {
				if(is_accepting(proxy(context, transition.id), is)) {
					current_state = &context.ref(transition.data.end_state);
					found = true;
				}
			}
		}
		if(!found) {
			break;
		}
	}

	return current_state->data.is_final;
}

}
