#pragma once

#include "alternative.hpp"
#include "name.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct Rule {
	Name name;
	bool does_accept_nothing = false;
	std::vector<Alternative> alternatives;

	Rule() = default;

	explicit
	Rule(std::string s)
	: name(std::move(s))
	{}

	operator const Name&() const noexcept {
		return name;
	}
};

inline
Rule rule(Name n) {
	auto r = Rule();
	r.name = std::move(n);
	return r;
}

inline
Rule rule(std::string s) {
	return rule(name(std::move(s)));
}

}
}
