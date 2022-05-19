#pragma once

#include "cursor.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>

#include <iterator>
#include <memory>
#include <vector>

namespace parsium {
namespace mckeeman {

struct Head {
	std::vector<Cursor> nested_cursors;
};

inline
Cursor& top_or(Head& h, common::UndefinedBehaviourTag) {
	return h.nested_cursors.back();
}

inline
std::vector<Head> fed_nothing(const Head& h) {

}

}
}
