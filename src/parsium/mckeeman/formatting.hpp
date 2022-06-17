#pragma once

#include <parsium/mckeeman/concept/grammar.hpp>
#include <parsium/mckeeman/builder/grammar.hpp>

#include <sstream>
#include <string>

namespace parsium {
namespace mckeeman {
namespace formatting {

inline
std::string to_string(const builder::Singleton& s) {
	auto result = std::stringstream();
	result << "'";
	if(s.codepoint == '\n') {
		result << "\\n";
	} else if(s.codepoint == '\r') {
		result << "\\r";
	} else if(s.codepoint == '\t') {
		result << "\\t";
	} else {
		result << s.codepoint;
	}
	result << "'";
	return result.str();
}

inline
std::string to_string(const builder::Characters& cs) {
	auto result = std::stringstream();
	result << "\"";
	for(auto c : cs.content) {
		if(c == '\n') {
			result << "\\n";
		} else if(c == '\r') {
			result << "\\r";
		} else if(c == '\t') {
			result << "\\t";
		} else {
			result << c;
		}
	}
	result << "\"";
	return result.str();
}

inline
std::string to_string(const builder::RangeExclude& re) {
	auto result = std::stringstream();
	auto& range = re.range;
	auto& excludes = re.excludes;
	result << to_string(range.lower_bound) << " . " << to_string(range.upper_bound);
	for(auto& exclude : excludes) {
		result << " - " << to_string(exclude);
	}
	return result.str();
}

struct LiteralFormatter {
	std::string operator()(const builder::Characters& cs) const {
		return to_string(cs);
	}

	std::string operator()(const builder::RangeExclude& re) const {
		return to_string(re);
	}

	std::string operator()(const builder::Singleton& s) const {
		return to_string(s);
	}
};

inline
std::string to_string(const builder::Literal& l) {
	auto result = std::stringstream();
	result << l.dispatch_to(LiteralFormatter());
	return result.str();
}

inline
std::string to_string(const builder::Name& n) {
	auto result = std::stringstream();
	result << n.string;
	return result.str();
}

struct ItemFormatter {
	std::string operator()(const builder::Literal& l) const {
		return to_string(l);
	}

	std::string operator()(const builder::Name& n) const {
		return to_string(n);
	}
};

inline
std::string to_string(const builder::Item& i) {
	return i.dispatch_to(ItemFormatter());
}

inline
std::string to_string(const builder::Alternative& a) {
	auto result = std::stringstream();
	result << "\t" << to_string(items(a)[0]);
	for(std::size_t i = 1; i < size(items(a)); ++i) {
		result << " " << to_string(items(a)[i]);
	}
	result << "\n";
	return result.str();
}

inline
std::string to_string(const builder::Rule& r) {
	auto result = std::stringstream();
	result << name(r).string << "\n";
	if(r.does_accept_nothing()) {
		result << "\t\"\"\n";
	}
	for(auto& alternative : alternatives(r)) {
		result << to_string(alternative);
	}
	result << "\n";
	return result.str();
}

inline
std::string to_string(const builder::Grammar& g) {
	auto result = std::stringstream();
	for(auto& rule : rules(g)) {
		result << to_string(rule);
	}
	return result.str();
}

}}}
