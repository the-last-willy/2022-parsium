#pragma once

#include "head.hpp"

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
	mh0.heads.insert(
		end(mh0.heads),
		std::make_move_iterator(begin(mh1.heads)),
		std::make_move_iterator(end(mh1.heads)));
}

inline
MultiHead _union(MultiHead mh0, MultiHead mh1) {
	unify(mh0, mh1);
	return mh0;
}

inline
MultiHead fed_nothing(const Grammar& g, const Head& h) {
	auto result = MultiHead();
	if(is_empty(h)) {
		result.is_accepting = true;
	} else {
		auto& top = top_or(h, UB);
		auto& item = current_item(top);
		if(auto literal = literal_or(item, nullptr)) {
			unify(result, h);
		} else if(auto name = name_or(item, nullptr)) {
			auto& rule_ = rule(g, *name);
			if(rule_.does_accept_nothing) {
				unify(result, fed_nothing(g, moved_to_next_item(h)));
			}
			for(auto& alternative : rule_.alternatives) {
				unify(result, fed_nothing(g, nested(h, alternative)));
			}
		}
	}
	return result;
}

inline
MultiHead fed(const Grammar& g, Head h, char symbol) {
	auto result = MultiHead();
	if(!is_empty(h)) {
		auto& top = top_or(h, UB);
		auto& item = current_item(top);
		if(auto name = name_or(item, nullptr)) {
			throw PreconditionViolation();
		} else if(auto literal = literal_or(item, nullptr)) {
			if(auto characters = characters_or(*literal, nullptr)) {
				if((*characters)[top.character_index] == symbol) {
					unify(result, fed_nothing(g, moved_to_next_character(h)));
				}
			} else if(auto range_exclude = range_exclude_or(*literal, nullptr)) {
				if(does_accept(*range_exclude, symbol)) {
					unify(result, fed_nothing(g, moved_to_next_item(h)));
				}
			} else if(auto singleton = singleton_or(*literal, nullptr)) {
				if(does_accept(*singleton, symbol)) {
					unify(result, fed_nothing(g, moved_to_next_item(h)));
				}
			}
		}
	}
	return result;
}

inline
MultiHead fed_nothing(const Grammar& g, const MultiHead& mh) {
	auto result = MultiHead();
	for(auto& head : mh.heads) {
		result = _union(std::move(result), fed_nothing(g, head));
	}
	return result;
}

inline
MultiHead fed(const Grammar& g, const MultiHead& mh, char symbol) {
	auto result = MultiHead();
	result.base_rule = mh.base_rule;
	for(auto& head : mh.heads) {
		result = _union(std::move(result), fed(g, head, symbol));
	}
	return result;
}

inline
MultiHead multi_head(const Grammar& g, const Rule& r) {
	auto result = MultiHead();
	result.base_rule = &r;
	for(auto& alternative : r.alternatives) {
		auto h = Head();
		h.nested_cursors.emplace_back(cursor(alternative));
		unify(result, fed_nothing(g, h));
	}
	return result;
}

}}
