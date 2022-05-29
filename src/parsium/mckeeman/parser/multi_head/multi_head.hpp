#pragma once

#include "parsium/mckeeman/parser/head.hpp"

#include <vector>

namespace parsium {
namespace mckeeman {

struct MultiHead {
	const Rule* base_rule = nullptr;

	bool is_accepting = false;
	std::vector<Head> heads;
};

inline
void unify(MultiHead& mh, Head h) {
	if(is_empty(h)) {
		mh.is_accepting = true;
	} else {
		mh.heads.push_back(std::move(h));
	}
}

inline
void unify(MultiHead& mh0, MultiHead mh1) {
	if(mh0.base_rule) {
		if(mh1.base_rule && mh0.base_rule != mh1.base_rule) {
			throw PreconditionViolation();
		}
	} else {
		mh0.base_rule = mh1.base_rule;
	}
	mh0.is_accepting = mh0.is_accepting || mh1.is_accepting;
	mh0.heads.insert(
		end(mh0.heads),
		std::make_move_iterator(begin(mh1.heads)),
		std::make_move_iterator(end(mh1.heads)));
}

inline
MultiHead _union(MultiHead mh0, MultiHead mh1) {
	unify(mh0, std::move(mh1));
	return mh0;
}

inline
MultiHead multi_head(const Grammar&, const Rule& r) {
	auto result = MultiHead();
	result.base_rule = &r;
	for(auto& alternative : r.alternatives) {
		auto h = Head();
		h.nested_cursors.emplace_back(cursor(alternative));
		unify(result, h);
	}
	return result;
}

}}
