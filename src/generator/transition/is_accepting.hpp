#pragma once

#include "proxy.hpp"

#include "generator/automaton/is_accepted.hpp"

#include <common/input_stream/input_stream.hpp>

#include <stdexcept>

namespace parsium {

inline
bool is_accepted(AutomatonProxy ap, common::InputStream& is);

inline
bool is_accepting(TransitionProxy tp, common::InputStream& is) {
	// auto& context = tp.context();
	auto& transition = tp.transition();

	if(transition.data.use_condition) {
		if(transition.data.condition == nullptr) {
			throw std::logic_error("Missing condition.");
		}
		auto b = transition.data.condition->evaluate(is.peek());
		if(b) {
			is.advance();
			return true;
		} else {
			return false;
		}
	} else if(transition.data.use_substate) {
		return is_accepted(proxy(context(tp), transition.data.substate), is);
	} else {
		throw std::logic_error("Empty transition.");
	}
}

}
