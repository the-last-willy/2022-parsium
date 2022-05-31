#pragma once

#include "generator.hpp"

#include <parsium/common/exception/precondition_violation.hpp>

#include <string>

namespace parsium {
namespace mckeeman {

inline
std::string indentation(std::size_t level) {
	auto single_indentation = "    ";
	auto result = std::string();
	result.reserve(level * std::strlen(single_indentation));
	for(std::size_t i = 0; i < level; ++i) {
		result += single_indentation;
	}
	return result;
}

inline
void indent(Generator& g) {
	g.indentation_level += 1;
	g.indentation = indentation(g.indentation_level);
}

inline
void unindent(Generator& g) {
	if(g.indentation_level == 0) {
		throw PreconditionViolation();
	} else {
		g.indentation_level -= 1;
		g.indentation = indentation(g.indentation_level);
	}
}

inline
const std::string& indentation(const Generator& g) {
	return g.indentation;
}

}}
