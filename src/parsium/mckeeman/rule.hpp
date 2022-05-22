#pragma once

#include "alternative.hpp"
#include "name.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
#include <parsium/common/tag/throw.hpp>

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

inline
std::size_t alternative_count(const Rule& r) {
	return size(r.alternatives);
}

inline
std::size_t alternative_index_or(const Rule& r, const Alternative& a, ThrowTag) {
	auto i = std::size_t(0);
	for(; i < alternative_count(r); ++i) {
		if(&a == &r.alternatives[i]) {
			break;
		}
	}
	if(i < alternative_count(r)) {
		return i;
	} else {
		throw PreconditionViolation();
	}
}

}
}
