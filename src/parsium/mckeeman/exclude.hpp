#pragma once

#include "range.hpp"

#include <memory>
#include <variant>

namespace parsium {
namespace mckeeman {

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

}
}
