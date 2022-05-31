#pragma once

#include "generator.hpp"

#include <iostream>

namespace parsium {
namespace mckeeman {

inline
std::string generate_cpp_declaration(Generator& g, const Rule& r) {
    
}

inline
std::string generate_cpp_declarations(Generator& g) {
    auto ss = std::stringstream();
    for(auto& rule : g.grammar->rules) {
        ss << generate_cpp_declaration(g, rule);
    }
    return ss.str();
}

inline
std::string generate_cpp_definitions(Generator& g) {
    
}

inline
std::string generate_cpp(Generator& g) {
    auto ss = std::stringstream();
    ss << generate_cpp_declarations(g);
    ss << generate_cpp_definitions(g);
    return ss.str();
}

}}
