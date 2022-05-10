#pragma once

#include "exclude.hpp"
#include "range.hpp"

#include <optional>

namespace parsium {
namespace mckeeman {

struct RangeExclude {
	Range range;
	std::optional<Exclude> exclude;
};

inline
RangeExclude range_exclude(Range r) {
	return RangeExclude({std::move(r), std::nullopt});
}

inline
RangeExclude range_exclude(Range r, Exclude e) {
	return RangeExclude({std::move(r), std::move(e)});
}

inline
bool does_accept(const RangeExclude& re, char c) {
	auto& [r, e] = re;
	return does_accept(r, c) && (!e || does_accept(*e, c));
}

inline
RangeExclude operator-(Range r, Exclude e) {
	return range_exclude(std::move(r), std::move(e));
}

inline
RangeExclude operator-(RangeExclude re, Exclude e) {
	if(re.exclude) {
		last_exclude(*re.exclude).next = std::make_unique<Exclude>(std::move(e));
	} else {
		re.exclude = std::move(e);
	}
	return re;
}

}
}
