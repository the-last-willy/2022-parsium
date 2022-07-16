#pragma once

#include "parsing_tree.hpp"

#include <cassert>
#include <string>

namespace parsium {

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_grammar();

// Rules.

// Instances.

MckeemanRule mckeeman_codepoint(char c);
MckeemanRule mckeeman_indentation();
MckeemanRule mckeeman_letter(char);
MckeemanRule mckeeman_name(const std::string&);
MckeemanRule mckeeman_newline();
MckeemanRule mckeeman_nothing(bool does_accept_nothing);
MckeemanRule mckeeman_range(char lb, char ub);
MckeemanRule mckeeman_singleton(char symbol);
MckeemanRule mckeeman_space();

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_codepoint(
    char c)
{
    // Missing second alternative.
    return MckeemanRule{
        .rule_ = "codepoint",
        .data_ = std::string(1, c)
    };
}

MckeemanRule mckeeman_indentation() {
    return MckeemanRule{
        .rule_ = "indentation",
        .alternatives_ = {
            MckeemanAlternative{{
                mckeeman_space(),
                mckeeman_space(),
                mckeeman_space(),
                mckeeman_space()
            }}
        }
    };
}

MckeemanRule mckeeman_letter(char c) {
    return MckeemanRule{
        .rule_ = "letter",
        .data_ = std::string(1, c)
    };
}

MckeemanRule mckeeman_name(const std::string& s) {
    assert(size(s) > 0);
    if(size(s) == 1) {
        return MckeemanRule{
            .rule_ = "name",
            .alternatives_ = {
                MckeemanAlternative{{
                    mckeeman_letter(s[0])
                }}
            }
        };
    } else {
        return MckeemanRule{
            .rule_ = "name",
            .alternatives_ = {
                MckeemanAlternative{{
                    mckeeman_letter(s[0]),
                    mckeeman_name(s.substr(1))
                }}
            }
        };
    }
}

MckeemanRule mckeeman_newline() {
    return MckeemanRule{
        .rule_ = "newline",
        .alternatives_ = {
            MckeemanAlternative{{
                mckeeman_codepoint('\n')
            }}
        }
    };
}

MckeemanRule mckeeman_nothing(
    bool does_accept_nothing)
{
    if(does_accept_nothing) {
        return MckeemanRule{
            .rule_ = "nothing",
            .alternatives_ = {{{
                mckeeman_indentation(),
                mckeeman_singleton('"'),
                mckeeman_singleton('"'),
                mckeeman_newline()
            }}}
        };
    } else {
        return MckeemanRule{
            .rule_ = "nothing"
        };
    }
}

MckeemanRule mckeeman_range(char lb, char ub) {
    return MckeemanRule{
        .rule_ = "range",
        .alternatives_ = {
            MckeemanAlternative{{
                mckeeman_singleton(lb),
                mckeeman_space(),
                mckeeman_singleton('.'),
                mckeeman_space(),
                mckeeman_singleton(ub)
            }}
        }
    };
}

MckeemanRule mckeeman_rule(
    const std::string& name,
    bool nothing,
    std::vector<MckeemanAlternative> alternatives)
{
    return MckeemanRule{
        .rule_ = "rule",
        .alternatives_ = {{{
            mckeeman_name(name),
            mckeeman_newline(),
            mckeeman_nothing(nothing)
        }}}
    };
}

MckeemanRule mckeeman_singleton(
    char codepoint)
{
    return MckeemanRule{
        .rule_ = "singleton",
        .alternatives_ = {
            MckeemanAlternative{{
                mckeeman_codepoint('\''),
                mckeeman_codepoint(codepoint),
                mckeeman_codepoint('\'')
            }}
        }
    };
}

MckeemanRule mckeeman_space() {
    return MckeemanRule{
        .rule_ = "space",
        .alternatives_ = {
            MckeemanAlternative{{
                mckeeman_singleton(' ')
            }}
        }
    };
}

}