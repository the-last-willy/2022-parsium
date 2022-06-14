#pragma once

namespace parsium {
namespace mckeeman {
namespace builder {

struct Range {
	Range(char lower_bound, char upper_bound)
		: lower_bound(lower_bound)
		, upper_bound(upper_bound)
	{}

	char lower_bound;
	char upper_bound;
};

inline
Range range(char lb, char ub) {
	return Range(lb, ub);
}

inline
bool does_accept(const Range& r, char c) {
	return c >= r.lower_bound && c <= r.upper_bound;
}

}}}
