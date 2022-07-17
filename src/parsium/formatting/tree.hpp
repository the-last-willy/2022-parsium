#pragma once

#include "parsium/mckeeman_tree.hpp"

#include <sstream>
#include <string>

namespace parsium {

std::string escaped(std::string s) {
	auto ret = std::string();
	for(auto c : s) {
		switch(c) {
			case '"': {
				ret += "\\\"";
				break;
			}
			case '\n': {
				ret += "\\n";
				break;
			}
			case '\r': {
				ret += "\\r";
				break;
			}
			default: {
				ret += c;
			}
		}
	}
	return ret;
}

class TreeFormatter {
public:
    int indent_level_ = 0;
    std::string indentation_;
    std::stringstream string_;

    void indent() {
		auto n = size(indentation_);
		if(indent_level_ > 0) {
			indentation_[n - 2] = '|';
			indentation_[n - 1] = ' ';
		}
		indentation_.resize(n + 2);
		indentation_[n + 0] = '+';
		indentation_[n + 1] = ' ';
		indent_level_ += 1;
    }

    void unindent() {
        indent_level_ -= 1;
		auto n = size(indentation_);
		indentation_.resize(n - 2);
		if(n >= 4) {
			indentation_[n - 4] = '+';
			indentation_[n - 3] = ' ';
		}
    }
};

void format(TreeFormatter& f, const MckeemanRule& r) {
    f.string_ << f.indentation_ << "\"" << r.rule_ << "\"";
    if(!r.data_.empty()) {
        f.string_ << " = \"" << escaped(r.data_) << "\"";
    }
    f.string_ << "\n";
    f.indent();
    for(int ai = 0; ai < size(r.alternatives_); ++ai) {
        auto& alternative = r.alternatives_[ai];
        if(size(r.alternatives_) > 1) {
            f.string_ << f.indentation_ << "ALT " << ai << "\n";
            f.indent();
        }
        for(int ii = 0; ii < size(alternative.items_); ++ii) {
            auto& item = alternative.items_[ii];
            format(f, item);
        }
        if(size(r.alternatives_) > 1) {
            f.unindent();
        }
    }
    f.unindent();
}

}
