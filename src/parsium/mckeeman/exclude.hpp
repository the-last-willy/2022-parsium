#pragma once

#include "range.hpp"

#include <memory>
#include <variant>

namespace parsium {
namespace mckeeman {

struct Exclude {
	// A range can also define a single codepoint.
	// Would be better than to have both a codepoint and a range.
	std::variant<char, Range> excluded_characters;

	// That's a linked list. Should be done outside Exclude.
	std::unique_ptr<Exclude> next;
};

inline
Exclude exclude(char c) {
	return Exclude({c});
}

inline
bool does_accept(const Exclude& e, char c) {
	const Exclude* current_exclude = &e;
	while(current_exclude) {
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
		} else {
			break;
		}
	}
	return true;
}

inline
Exclude& last_exclude(Exclude& e) {
	auto current = &e;
	while(current->next) {
		current = current->next.get();
	}
	return *current;
}

}
}
