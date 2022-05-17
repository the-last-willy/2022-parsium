#pragma once

#include "item.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct Alternative {
	std::vector<Item> items;
};

inline
std::size_t item_count(const Alternative& a) {
	return size(a.items);
}

}
}
