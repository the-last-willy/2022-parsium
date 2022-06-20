#pragma once

// #include "parsium/json/formatting/"

// #include <parsium/json/>
#include <parsium/json/building.hpp>

// #include <parsium/>

#include <sstream>

namespace parsium {
namespace json {
namespace formatting {

class Formatter {

public:
	std::size_t indent_level = 0;
	std::stringstream string;

	void indent() {
		indent_level += 1;
	}

	void unindent() {
		indent_level -= 1;
	}
};

//

void format(Formatter& f, const building::Array& a);
void format(Formatter& f, const building::Object& o);
void format(Formatter& f, const building::Number& n);
void format(Formatter& f, const building::String& s);

struct ElementFormatter {
	Formatter* formatter_;

	ElementFormatter(Formatter& f)
	: formatter_(&f)
	{}

	template<typename T>
	void operator()(const T& t) const {
		format(*formatter_, t);
	}
};

void format(Formatter& f, const building::Array& a) {
	f.string << "-array-";
}

void format(Formatter& f, const building::Object& o) {
	f.string << "-object-";
}

void format(Formatter& f, const building::Number& n) {
	f.string << n.representation();
}

void format(Formatter& f, const building::String& s) {
	f.string << "-string-";
}

//

inline
void format(Formatter& f, const building::Json& j) {
	if(auto element = j.element_or(nullptr)) {
		element->dispatch_to(ElementFormatter(f));
	}
}

}}}
