#pragma once

#include "../alternative.hpp"
#include "../grammar.hpp"
#include "../name.hpp"
#include "../rule.hpp"

#include <parsium/common/tag/undefined_behaviour.hpp>

namespace parsium {
namespace mckeeman {

inline
const Rule_ auto* rule_or(const Grammar_ auto& g, const Name_ auto& n, decltype(nullptr)) {
	using T = Traits<decltype(g)>;
	const Rule<T>* result = nullptr;
	for(const Rule_ auto& r : rules(g)) {
		if(name(r) == n) {
			result = &r;
		}
	}
	return result;
}

inline
const Rule_ auto& rule_or(const Grammar_ auto& g, const Name_ auto& n, decltype(UB)) {
	return *rule_or(g, n, nullptr);
}

}}
