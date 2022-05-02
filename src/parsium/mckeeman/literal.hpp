#pragma once

#include <memory>
#include <utility>
#include <string>
#include <variant>

namespace parsium {
namespace mckeeman {

struct Range {
	char lower_bound;
	char upper_bound;
};

inline
Range range(char lb, char ub) {
	return Range(lb, ub);
}

inline
bool does_accept(const Range& r, char c) {
	return c >= r.lower_bound and c <= r.upper_bound;
}

struct Exclude {
	std::variant<char, Range> excluded_characters;
	std::unique_ptr<Exclude> next;
};

bool does_accept(const Exclude& e, char c) {
	const Exclude* current_exclude = &e;
	do {
		if(auto ch = std::get_if<char>(&current_exclude->excluded_characters)) {
			if(*ch == c) {
				return false;
			}
		} else if(auto r = std::get_if<Range>(&current_exclude->excluded_characters)) {
			if(does_accept(*r, c)) {
				return false;
			}
		}
		if(current_exclude->next) {
			current_exclude = current_exclude->next.get();
		}
	} while(current_exclude);
	return true;
}

struct Literal {
	std::variant<char, std::pair<Range, Exclude>, std::string> content;
};

inline
bool does_accept(char codepoint, char c) {
	return c == codepoint;
}

inline
bool does_accept(const std::pair<Range, Exclude>& p, char c) {
	auto& [r, e] = p;
	return does_accept(r, c) and does_accept(e, c);
}

inline
bool does_accept(const std::string& s, char c) {
	return s.size() > 0 and c == s.front();
}

inline
Literal characters_literal(std::string characters) {
	return Literal({std::move(characters)});
}

inline
Literal range_exclude_literal(Range range, Exclude exclude) {
	return Literal({std::make_pair(std::move(range), std::move(exclude))});
}

inline
Literal singleton_literal(char codepoint) {
	return Literal({codepoint});
}

inline
bool does_accept(const Literal& l, char c) {
	return std::visit([c](auto&& a) -> bool {
		return does_accept(a, c);
	}, l.content);
}

}
}
