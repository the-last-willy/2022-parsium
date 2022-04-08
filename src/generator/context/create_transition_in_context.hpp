#pragma once

#include "generator/transition/proxy.hpp"
#include "generator/transition/transition.hpp"

#include <vector>

namespace parsium {

inline
TransitionProxy create_transition_in(Context& c) {
	auto id = TransitionId();
	id.index = c.transitions.size();
	auto& transition = c.transitions.emplace_back();
	transition.id = id;
	return proxy(c, transition.id);
}

}
