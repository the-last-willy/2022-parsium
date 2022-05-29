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

inline
bool is_accepting(const Grammar& g, const Rule& r) {
	if(r.does_accept_nothing) {
		return true;
	} else {
		auto is_alternative_accepting = true;
		for(auto& alternative : r.alternatives) {
			is_alternative_accepting = true;
			for(std::size_t i = 0; i < item_count(alternative); ++i) {
				auto& item = alternative.items[i];
				if(literal_or(item, nullptr)) {
					is_alternative_accepting = false;
					break;
				} else if(auto name = name_or(item, nullptr)) {
					if(!is_accepting(g, rule(g, *name))) {
						is_alternative_accepting = false;
						break;
					}
				}
			}
			if(is_alternative_accepting) {
				break;
			}
		}
		return is_alternative_accepting;
	}
}

}
}
