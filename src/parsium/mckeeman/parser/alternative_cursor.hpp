#pragma once

#include "rule_cursor.hpp"

#include "parsium/mckeeman/alternative.hpp"

namespace parsium {
namespace mckeeman {

class AlternativeCursor {
    RuleCursor rule_cursor_;

public:
    AlternativeCursor(RuleCursor rule)
    : rule_(&r)
    {}

    const Rule* rule_or(std::nullptr_t) const {
        return rule_;
    }

    Rule* rule_or(std::nullptr_t) {
        return rule_;
    }
};

}
}
