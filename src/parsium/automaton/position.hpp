#pragma once

#include "parsium/automaton/state.hpp"

#include <vector>

namespace parsium {
namespace automaton {

class Position {
public:
	std::vector<const State*> state_stack;
};

void pop(Position& p) {
	p.state_stack.pop_back();
}

const State* top(const Position& p) {
	return p.state_stack.back();
}

const State*& top(Position& p) {
	return p.state_stack.back();
}

void push(Position& p, const State& s) {
	p.state_stack.push_back(&s);
}

}
}