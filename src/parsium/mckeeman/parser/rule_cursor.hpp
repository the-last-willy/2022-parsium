#pragma once

#include "parsium/mckeeman/rule.hpp"

namespace parsium {
namespace mckeeman {

class RuleCursor {
    Rule* rule_;

public:
    RuleCursor(Rule& r)
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
