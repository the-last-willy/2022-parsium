#pragma once

#include <cstdlib>

namespace parsium {

struct StateId {
	std::size_t index;

	bool operator==(const StateId&) const = default;
};

}
