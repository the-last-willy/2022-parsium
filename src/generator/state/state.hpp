#pragma once

#include "id.hpp"

namespace parsium {

struct StateData {
	bool is_final = false;
};

struct State {
	StateId id;
	StateData data;

	operator StateId() const {
		return id;
	}
};

}
