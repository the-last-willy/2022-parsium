#pragma once

#include "rule.hpp"

#include <stdexcept>

namespace parsium {
namespace mckeeman {

struct Grammar {
	std::vector<Rule> rules;
};

inline
const Rule& rule(const Grammar& g, const Name& n) {
	for(auto& rule : g.rules) {
		if(rule.name == n) {
			return rule;
		}
	}
	throw std::runtime_error("No rule with name.");
}

inline
Rule& rule(Grammar& g, const Name& n) {
	for(auto& rule : g.rules) {
		if(rule.name == n) {
			return rule;
		}
	}
	throw std::runtime_error("No rule with name.");
}

}
}
