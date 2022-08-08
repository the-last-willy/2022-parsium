#pragma once

#include "parsium/mckeeman_node.hpp"

#include <sstream>
#include <string>

namespace parsium {

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
//
//void format(TreeFormatter& f, const MckeemanRule& r) {
//    f.string_ << f.indentation_ << "\"" << r.rule_ << "\"";
//    if(!r.data_.empty()) {
//        f.string_ << " = \"" << escaped(r.data_) << "\"";
//    }
//    f.string_ << "\n";
//    f.indent();
//    for(int ai = 0; ai < size(r.alternatives_); ++ai) {
//        auto& alternative = r.alternatives_[ai];
//        if(size(r.alternatives_) > 1) {
//            f.string_ << f.indentation_ << "ALT " << ai << "\n";
//            f.indent();
//        }
//        for(int ii = 0; ii < size(alternative.items_); ++ii) {
//            auto& item = alternative.items_[ii];
//            format(f, item);
//        }
//        if(size(r.alternatives_) > 1) {
//            f.unindent();
//        }
//    }
//    f.unindent();
//}
//

void format(TreeFormatter&, const MckeemanNode&);
void format_item(TreeFormatter&, const MckeemanNode&);


inline
void format_item(TreeFormatter& f, const MckeemanNode& n) {
	f.string_ << f.indentation_ << "\"" << n.name_ << "\"";
	if(has_literal(n)) {
		f.string_ << " = \"" << escaped(*literal(n)) << "\"";
	}
	f.string_ << "\n";

	f.indent();

	for(int ai = 0; ai < size(n.alternatives_); ++ai) {
		auto& alternative = n.alternatives_[ai];
		if(size(n.alternatives_) > 1) {
			f.string_ << f.indentation_ << "ALT " << ai << "\n";
			f.indent();
		}
		format(f, alternative);
		//		for(auto it = next(n, ai); it; it = next(*it, ai)) {
		//			format(f, *it);
		//		}
		if(size(n.alternatives_) > 1) {
			f.unindent();
		}
	}
	f.unindent();
}

inline
void format(TreeFormatter& f, const MckeemanNode& n) {
	for(auto item = &n; item != nullptr; item = next_item(*item)) {
		format_item(f, *item);
	}
}

}
