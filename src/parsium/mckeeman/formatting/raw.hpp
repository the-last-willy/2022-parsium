#pragma once

#include "parsium/mckeeman/storing/node.hpp"

#include <sstream>
#include <string>

namespace parsium::mckeeman {

class RawFormatter {
public:
	std::stringstream stream_;

	int depth = 0;
};

inline
void format(RawFormatter& f, const StorageNode& n) {
	auto it = &n;
	do {
		if(is_alternative(*it)) {
			f.stream_ << "alt\n";
		} else if(is_item(*it)) {
			if(is_name(*it)) {
				f.stream_ << "name=" << *name(*it);
				if(is_literal(*it)) {
					f.stream_ << ", ";
				}
			}
			if(is_literal(*it)) {
				f.stream_ << "lit=" << *literal(*it);
			}
			f.stream_ << "\n";
		}
		it = nullptr;
	} while(it != nullptr);
}

}