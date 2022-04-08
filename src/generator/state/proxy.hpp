#pragma once

#include "id.hpp"
#include "state.hpp"

#include "generator/context/context.hpp"

namespace parsium {

struct StateProxy {
	Context* context;
	StateId id;

	StateProxy(Context& c, StateId id)
	: context(&c)
	, id(id)
	{}

	operator StateId() const noexcept {
		return id;
	}

	State* operator->() const {
		return &context->ref(id);
	}
};

inline
StateProxy proxy(Context& c, StateId id) {
	return StateProxy(c, id);
}

}