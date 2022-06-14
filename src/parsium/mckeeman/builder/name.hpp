#pragma once

#include <string>
#include <string_view>

namespace parsium {
namespace mckeeman {
namespace builder {

class Name {
public:
	std::string string;

	Name() = default;

	Name(std::string s)
	: string(std::move(s))
	{}

	Name(const char* str)
	: string(str)
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

}}}
