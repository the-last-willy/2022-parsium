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

}}
