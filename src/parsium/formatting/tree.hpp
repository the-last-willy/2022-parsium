#pragma once

#include "parsium/mckeeman_tree.hpp"

#include <sstream>
#include <string>

namespace parsium {

class TreeFormatter {
public:
    int indent_level_ = 0;
    std::string indentation_;
    std::stringstream string_;

    void indent() {
        indent_level_ += 1;
        indentation_ = "";
        for(int i = 0; i < indent_level_; ++i) {
            indentation_ += "  ";
        }
    }

    void unindent() {
        indent_level_ -= 1;
        indentation_ = "";
        for(int i = 0; i < indent_level_; ++i) {
            indentation_ += "  ";
        }
    }
};

void format(TreeFormatter& f, const MckeemanRule& r) {
    f.string_ << f.indentation_ << "\"" << r.rule_ << "\"";
    if(!r.data_.empty()) {
        f.string_ << " = " << r.data_;
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
