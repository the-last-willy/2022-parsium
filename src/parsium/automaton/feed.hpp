#pragma once

#include "parsium/automaton/position.hpp"
#include "parsium/automaton/state.hpp"

#include <parsium/common/input_stream.hpp>

#include <optional>
#include <stdexcept>

namespace parsium {
namespace automaton {

inline
bool feed_simple(Position& p, char symbol) {
	for(auto& transition : top(p)->transitions) {
		if(transition.symbol == symbol) {
			top(p) = transition.end_state.get();
			return true;
		}
	}
	if(top(p)->type == StateType::composite) {
		pop(p);
	}
	return false;
}

inline
void feed(Position& p, char symbol) {
	if(p.state_stack.empty()) {
		return;
	}

	auto current = top(p);
	switch(current->type) {
		case StateType::composite: {
			push(p, *current->composite_nested_state);
			feed(p, symbol);
		}
		case StateType::simple: {

		}
		default: {
			throw std::logic_error("!impl.");
		}
	}
}

inline
std::optional<const State*> fed(const State& s, char symbol) {
	for(auto& transition : s.transitions) {
		if(transition.symbol == symbol) {
			return transition.end_state.get();
		}
	}
	return std::nullopt;
}

inline
const State& fed_until_halt(const State& s, common::InputStream& is) {
	auto current_position = std::optional<const State*>(&s);

	while(!is.is_done()) {
		auto previous_position = *current_position;

		current_position = fed(**current_position, is.peek());

		if(!current_position) {
			return *previous_position;
		}

		is.advance();
	}

	return **current_position;
}

}
}
