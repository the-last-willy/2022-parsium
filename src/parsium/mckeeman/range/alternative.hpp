#pragma once

#include "parsium/mckeeman/alternative.hpp"
#include "parsium/mckeeman/rule.hpp"

namespace parsium {
namespace mckeeman {

struct AlternativeIterator {
    const Rule* rule = nullptr;
    std::size_t alternative_index = 0;
};

struct AlternativeSentinel {};

inline
AlternativeIterator begin(const Rule& r) {
    return AlternativeIterator({
        .rule = &r,
    });
}

inline
AlternativeSentinel end(const Rule&) {
    return AlternativeSentinel();
}

// Operators.

inline
AlternativeIterator& operator++(AlternativeIterator& ai) {
    ai.alternative_index += 1;
}

inline
const Alternative& operator*(const AlternativeIterator& ai) {
    return ai.rule->alternatives[ai.alternative_index];
}

}
}
