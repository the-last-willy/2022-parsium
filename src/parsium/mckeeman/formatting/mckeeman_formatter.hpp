#pragma once

#include "parsium/mckeeman_tree.hpp"

#include <cassert>
#include <sstream>
#include <stdexcept>

namespace parsium {

class MckeemanFormatter {
public:
    int indent_ = -1;
    std::stringstream string_;
};

void format_codepoint(MckeemanFormatter& f, const MckeemanRule& codepoint);
void format_singleton(MckeemanFormatter& f, const MckeemanRule& singleton);

void format_codepoint(MckeemanFormatter& f, const MckeemanRule& codepoint) {
    assert(codepoint.rule_ == "codepoint");
    assert(size(codepoint.data_) == 1);
    f.string_ << codepoint.data_;
}

void format_rules(MckeemanFormatter& f, const MckeemanRule& rules) {
    if(rules.rule_ != "rules")
        throw std::logic_error("The rule is expected to be `rules`.");
    
}

void format_singleton(MckeemanFormatter& f, const MckeemanRule& singleton) {
    assert(singleton.rule_ == "singleton");
    if(size(singleton.alternatives_) == 1) {
        auto& items = singleton.alternatives_[0].items_;
        assert(size(items) == 3);
        format_codepoint(f, items[0]);
        format_codepoint(f, items[1]);
        format_codepoint(f, items[2]);
    } else {
        assert(false);
    }
}

void format_grammar(MckeemanFormatter& f, const MckeemanRule& grammar) {
    if(grammar.rule_ != "grammar")
        throw std::logic_error("Formatting a grammar but no grammar was provided.");
    
}

}