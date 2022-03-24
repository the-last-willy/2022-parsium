#pragma once

#include <cstdlib>

namespace parsium {

struct StateId {
	std::size_t index;

	StateId() = delete;
};

class AnyState {
	StateId id;

public:
	AnyState(StateId id)
	: id(id)
	{}
};

struct HierarchicalState : public AnyState {

};

struct SimpleState : public AnyState {
	SimpleState(StateId id)
	: AnyState(id)
	{}
};

}