#pragma once

#include "parsium/mckeeman/storing/iterating.hpp"
#include "parsium/mckeeman/storing/node.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

namespace parsium::mckeeman {

class Validator {
public:
	const StorageNode* grammar_;
	std::map<std::string, const StorageNode*> rules_;

	Validator(const StorageNode& n)
	: grammar_(&n)
	{
		assert(*name(n) == "grammar");
		auto it = child_with_name(n, "rules");
		assert(it != nullptr);
		do {
			assert(has_child(*it));
			it = child(*it);
			assert(*name(*it) == "rule");
			auto na = child_with_name(*it, "name");
			assert(na != nullptr);

			it = sibling_with_name(*it, "rules");
		} while(it != nullptr);
	}
};

}
