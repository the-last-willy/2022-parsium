#pragma once

#include "parsium/mckeeman/grammar.hpp"

namespace parsium {
namespace mckeeman {

struct Generator {
    const Grammar* grammar;

	std::size_t indentation_level = 0;
	std::string indentation = "";
};

}}
