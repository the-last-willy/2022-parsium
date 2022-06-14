#pragma once

#include "parsium/mckeeman/builder/rule/rule.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

class RuleMetadata {
	bool does_notify_on_enter_ = false;

public:
	bool does_notify_on_enter() const {
		return does_notify_on_enter_;
	}

	//

	void notify_on_enter(bool b) {
		does_notify_on_enter_ = b;
	}
};

}}
