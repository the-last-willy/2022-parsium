#pragma once

#include "parsium/mckeeman/storing/node.hpp"

#include "parsium/common/std/string.hpp"

#include <sstream>
#include <string>

namespace parsium::mckeeman {

class RawFormatter {
public:
	int depth_ = 0;

	std::stringstream stream_;
	std::string indentation_;

	void indent() {
		auto n = size(indentation_);
		if(depth_ > 0) {
			indentation_[n - 2] = '|';
			indentation_[n - 1] = ' ';
		}
		indentation_.resize(n + 2);
		indentation_[n + 0] = '+';
		indentation_[n + 1] = ' ';
		depth_ += 1;
	}

	void unindent() {
		assert(depth_ > 0);
		depth_ -= 1;
		auto n = size(indentation_);
		indentation_.resize(n - 2);
		if(n >= 4) {
			indentation_[n - 4] = '+';
			indentation_[n - 3] = ' ';
		}
	}
};

inline
void format(RawFormatter& f, const StorageNode& n) {
	auto it = &n;
	do {
		{
			f.stream_ << f.indentation_;
			if(is_alternative(*it)) {
				f.stream_ << "-";
			} else if(is_item(*it)) {
				if(is_name(*it)) {
					f.stream_ << "\"" << *name(*it) << "\" ";
				}
				if(is_literal(*it)) {
					f.stream_ << "= \"" << escaped(*literal(*it)) << "\"";
				}
			}
			f.stream_ << "\n";
		}
		if(has_child(*it)) {
			it = child(*it);
			f.indent();
		} else {
			do {
				if(has_sibling(*it)) {
					it = sibling(*it);
					break;
				} else {
					if(has_parent(*it)) {
						it = parent(*it);
						f.unindent();
					} else {
						it = nullptr;
						break;
					}
				}
			} while(it != nullptr);
		}
	} while(it != nullptr);
}

}