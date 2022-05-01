#pragma once

#include "transition.hpp"

#include <vector>

namespace parsium {
namespace automaton {

enum class StateType {
	unspecified,

	composite,
	simple,
};

struct State {
	bool is_accepting = false;

	std::vector<Transition> transitions;

	StateType type = StateType::unspecified;

	State* composite_nested_state = nullptr;

	explicit
	State(bool is_accepting)
	: is_accepting(is_accepting)
	{}
};

inline
State composite_state(bool is_accepting, State& nested_state) {

}

inline
State simple_state(bool is_accepting) {

}

}
}