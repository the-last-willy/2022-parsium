#pragma once

#include "generator/automaton/automaton.hpp"
#include "generator/context/context.hpp"

namespace parsium {

struct AutomatonProxy {
	Context* context_ = nullptr;
	AutomatonId id_ = AutomatonId{0};

	AutomatonProxy() = default;


	AutomatonProxy(Context& c, AutomatonId& id)
	: context_(&c)
	, id_(id)
	{}

	Automaton* operator->() {
		return &automaton();
	}

	operator AutomatonId() const noexcept {
		return id_;
	}

	const Automaton& automaton() const {
		return context().ref(id_);
	}

	Automaton& automaton() {
		return context().ref(id_);
	}

	const Context& context() const {
		return *context_;
	}

	Context& context() {
		return *context_;
	}
};

inline
AutomatonProxy proxy(Context& c, AutomatonId id) {
	return AutomatonProxy(c, id);
}

}
