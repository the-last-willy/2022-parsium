#pragma once

#include "parsium/mckeeman/builder/item/builder.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

class AlternativeBuilder {
public:

private:
	std::vector<ItemBuilder> items_;
};

}}
