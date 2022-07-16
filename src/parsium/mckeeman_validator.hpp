#pragma once

#include "parsium/mckeeman_tree.hpp"

#include <cassert>
#include <vector>

namespace parsium {

class MckeemanValidator {
public:
    MckeemanRule* grammar_ = nullptr;
    std::vector<MckeemanRule*> rules_;

    MckeemanValidator(const MckeemanRule& r) {

    }
};

inline
bool does_validate(const MckeemanValidator& v, const MckeemanRule& parse_tree) {

    
}

}
