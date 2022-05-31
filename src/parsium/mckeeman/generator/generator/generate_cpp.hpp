#pragma once

#include "indentation.hpp"
#include "generator.hpp"

#include <sstream>

namespace parsium {
namespace mckeeman {

inline
std::string generate_cpp_function_declarations(Generator&, const Rule& r) {
    auto ss = std::stringstream();
	ss << "bool parse_" << r.name.string << "(Parser& p, char symbol);\n";
	return ss.str();
}

inline
std::string generate_cpp_function_declarations(Generator& g) {
    auto ss = std::stringstream();
	ss << "// Function declarations.\n\n";
    for(auto& rule : g.grammar->rules) {
        ss << generate_cpp_function_declarations(g, rule);
    }
    return ss.str();
}

inline
std::string generate_cpp_function_definitions(Generator& g, const Rule& r, const Alternative& a) {
	auto ss = std::stringstream();

	return ss.str();
}

inline
std::string generate_cpp_function_definitions(Generator& g, const Rule& r) {
	auto ss = std::stringstream();
	ss << indentation(g) << "bool parse_" << r.name.string << "(Parser& p, char symbol) {\n";
		indent(g);
		ss << indentation(g) << "if(is_halted(p)) {\n";
			indent(g);
			ss << indentation(g) << "p.is_accepting = false;\n";
			ss << indentation(g) << "return false;\n";
			unindent(g);
		ss << indentation(g) << "} else {\n";
			indent(g);
			for(auto& alternative : r.alternatives) {
				ss << generate_cpp_function_definitions(g, r, alternative);
			}
			unindent(g);
		ss << indentation(g) << "}\n";
		unindent(g);
	ss << indentation(g) << "}\n\n";
	return ss.str();
}

inline
std::string generate_cpp_function_definitions(Generator& g) {
	auto ss = std::stringstream();
	ss << "// Function definitions.\n\n";
	for(auto& rule : g.grammar->rules) {
		ss << generate_cpp_function_definitions(g, rule);
	}
	return ss.str();
}

inline
std::string generate_cpp(Generator& g) {
    auto ss = std::stringstream();
    ss << generate_cpp_function_declarations(g);
	ss << "\n";
    ss << generate_cpp_function_definitions(g);
    return ss.str();
}

}}
