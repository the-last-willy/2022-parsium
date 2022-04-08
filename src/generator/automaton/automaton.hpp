#pragma once

#include "generator/state/state.hpp"

#include <cstdlib>
#include <string>
#include <vector>

namespace parsium {

struct AutomatonId {
	std::size_t index;
};

struct AutomatonData {
	std::vector<StateId> states;

	StateId start_state;

	bool does_notify = false;
};

struct Automaton {
	AutomatonId id;
	AutomatonData data;
};

}