#pragma once

#include "indentation.hpp"
#include "generator.hpp"

#include <sstream>

namespace parsium {
namespace mckeeman {

inline
std::string generate_cpp_function_declarations(Generator&, const Rule& r) {
    auto ss = std::stringstream();
	ss << "bool parse_rule_" << r.name.string << "(Parser& p);\n";
	for(auto& alternative : r.alternatives) {
		ss << "bool parse_alternative_" << r.name.string << "_" << alternative_index_or(r, alternative, _throw) << "(Parser& p);\n";
		for(std::size_t item_i = 0; item_i < size(alternative.items); ++item_i) {
			auto& item = alternative.items[item_i];
			ss << "bool parse_item_" << r.name.string << "_" << alternative_index_or(r, alternative, _throw) << "_" << item_i << "(Parser& p);\n";
			if(auto literal = literal_or(item, nullptr)) {

			} else if(auto name = name_or(item, nullptr)) {
				ss << "bool parse_name_" << r.name.string << "_" << alternative_index_or(r, alternative, _throw) << "_" << item_i << "(Parser& p);\n";
			}
		}
	}
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
std::string generate_cpp_function_definitions(Generator&, const Rule&, const Alternative&) {
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
