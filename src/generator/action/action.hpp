#pragma once

namespace parsium {

enum class ActionType {
	none,
	notify,

	count
};

struct Action {
	ActionType type = ActionType::none;
};

}
