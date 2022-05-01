#pragma once

#include <functional>
#include <memory>

namespace parsium {
namespace automaton {

struct State;

enum class TransitionType {
	uninitialized,

	epsilon_transition
	symbol_transition,
};

struct Transition {
	TransitionType type = TransitionType::uninitialized;

	char symbol = '\0';

	std::shared_ptr<State> end_state = nullptr;
};

inline
Transition transition(char symbol, std::shared_ptr<State> state) {
	auto transition = Transition();

	transition.type = TransitionType::symbol_transition;

	transition.symbol = symbol;
	transition.end_state = std::move(state);

	return transition;
}

inline
Transition character_transition(char symbol, std::shared_ptr<State> state) {
	auto transition = Transition();

	transition.type = TransitionType::symbol_transition;

	transition.symbol = symbol;
	transition.end_state = std::move(state);

	return transition;
}

inline
Transition epsilon_transition(std::shared_ptr<State> dst) {
	auto t = Transition();

	t.type = TransitionType::epsilon_transition;

	t.end_state = dst;

	return t;
}

}
}
