#pragma once

#include "generator/state/state.hpp"

#include <vector>

namespace parsium {

struct Position
{
	std::vector<StateId> state_stack;
};

StateId top(const Position& position)
{
	return position.state_stack.back();
}

void pop(Position& position)
{
	position.state_stack.pop_back();
}

}