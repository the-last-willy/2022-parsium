#pragma once

#include "context.hpp"

#include "generator/state/proxy.hpp"
#include "generator/state/state.hpp"

#include <vector>

namespace parsium {

inline
StateProxy create_state_in(Context& c) {
	auto id = StateId();
	id.index = c.states.size();
	auto& state = c.states.emplace_back();
	state.id = id;
	return proxy(c, state.id);
}

}
