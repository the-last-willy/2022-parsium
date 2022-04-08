#pragma once

#include "transition.hpp"

#include "generator/context/context.hpp"

namespace parsium {

struct TransitionProxy {
	Context* context_ = nullptr;
	TransitionId id_;

	TransitionProxy(Context& c, TransitionId& id)
		: context_(&c)
		, id_(id)
	{}

	const Transition& transition() const {
		return context().ref(id_);
	}

	Transition& transition() {
		return context().ref(id_);
	}

	const Context& context() const {
		return *context_;
	}

	Context& context() {
		return *context_;
	}

	Transition* operator->() {
		return &context().ref(id_);
	}
};

inline
TransitionProxy proxy(Context& c, TransitionId id) {
	return TransitionProxy(c, id);
}

inline
Context& context(TransitionProxy proxy) {
	return *proxy.context_;
}

inline
Transition& transition(TransitionProxy proxy) {
	return context(proxy).ref(proxy.id_);
}

}
