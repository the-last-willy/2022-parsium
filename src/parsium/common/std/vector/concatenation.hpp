#pragma once

#include <iterator>
#include <vector>

namespace parsium {
namespace common {

template<typename T>
std::vector<T> concatenation(std::vector<T> l0, std::vector<T> l1) {
    l0.insert(
        end(l0),
        make_move_iterator(begin(l0)),
        make_move_iterator(end(l1)));
    return l0;
} 

}}
