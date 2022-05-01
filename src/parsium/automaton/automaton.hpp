#pragma once

#include "state.hpp"

#include <memory>
#include <vector>

namespace parsium {
namespace automaton {

struct Automaton {
	std::shared_ptr<State> start_state = nullptr;
};

inline
Automaton automaton(std::shared_ptr<State> start_state) {
	Automaton result;
	result.start_state = std::move(start_state);
	return result;
}

}
}