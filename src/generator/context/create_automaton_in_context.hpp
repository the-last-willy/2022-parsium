#pragma once

#include "context.hpp"

#include "generator/automaton/automaton.hpp"
#include "generator/automaton/proxy.hpp"

#include <vector>

namespace parsium {

inline
AutomatonProxy create_automaton_in(Context& c) {
	auto id = AutomatonId();
	id.index = c.automata.size();
	auto& state = c.automata.emplace_back();
	state.id = id;
	return proxy(c, state.id);
}

}
