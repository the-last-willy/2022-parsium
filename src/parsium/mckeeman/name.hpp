#pragma once

#include <string>

namespace parsium {
namespace mckeeman {

struct Name {
	std::string string;

	Name() = default;

	Name(std::string s)
	: string(std::move(s))
	{}
};

inline
Name name(std::string s) {
	return Name(std::move(s));
}

inline
bool operator==(const Name& n0, const Name& n1) {
	return n0.string == n1.string;
}

}
}
