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
		for(std::size_t i = 0; i < indent_level; ++i) {
			string << "  ";
		}
	}

	void increase_indent() {
		indent_level += 1;
	}

	void decrease_indent() {
		indent_level -= 1;
	}
};

//

void format(Formatter& f, const building::Array& a);
void format(Formatter& f, const building::Object& o);
void format(Formatter& f, const building::Member& m);
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

inline
void format(Formatter& f, const building::Element& e) {
	e.dispatch_to(ElementFormatter(f));
}

inline
void format(Formatter& f, const building::Array& a) {
	f.string << "[";
	auto& elements = a.elements();
	if(elements.empty()) {
		f.string << "]";
	} else {
		f.string << "\n";
		f.increase_indent();
		f.indent();
		format(f, elements[0]);
		for(std::size_t i = 1; i < size(elements); ++i) {
			f.string << ",\n";
			f.indent();
			format(f, elements[i]);
		}
		f.string << "\n";
		f.decrease_indent();
		f.indent();
		f.string << "]";
	}
}

inline
void format(Formatter& f, const building::Object& o)
{
	f.string << "{";
	auto &members = o.members();
	if(members.empty())
	{
		f.string << "}";
	}
	else
	{
		f.string << "\n";
		f.increase_indent();
		f.indent();
		format(f, members[0]);
		for(std::size_t i = 1; i < size(members); ++i) {
			f.string << ",\n";
			f.indent();
			format(f, members[i]);
		}
		f.string << "\n";
		f.decrease_indent();
		f.indent();
		f.string << "}";
	}
}

inline
void format(Formatter& f, const building::Member& m) {
	format(f, m.string());
	f.string << ": ";
	format(f, m.element());
}

inline
void format(Formatter& f, const building::Number& n) {
	f.string << n.representation();
}

inline
void format(Formatter& f, const building::String& s) {
	f.string << "\"" << s.characters() << "\"";
}

//

inline
void format(Formatter& f, const building::Json& j) {
	if(auto element = j.element_or(nullptr)) {
		format(f, *element);
	}
}

}}}
