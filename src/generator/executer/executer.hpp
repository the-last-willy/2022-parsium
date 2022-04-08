#pragma once

#include "generator/automaton/automaton.hpp"
#include "generator/automaton/proxy.hpp"
#include "generator/state/state.hpp"

#include <common/input_stream/input_stream.hpp>

#include <vector>

namespace parsium {

class Executer {
public:
	AutomatonProxy automaton;
	common::InputStream input;

	std::vector<StateId> states = {};

public:
	Executer(
		 AutomatonProxy automaton,
		 common::InputStream input)
	: automaton(automaton)
	, input(std::move(input))
	{
		states.push_back(automaton->data.start_state);
	}
};

void do_one_step(Executer& executer) {
	auto next_states = std::vector<StateId>();

}

}
