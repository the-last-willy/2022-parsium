#pragma once

namespace parsium {
namespace mckeeman {

struct Singleton {
	char codepoint;

	Singleton() = default;

	Singleton(char c)
	: codepoint(c)
	{}

	operator char() const {
		return codepoint;
	}
};

inline
bool does_accept(const Singleton& s, char c) {
	return s.codepoint == c;
}

}}
