#pragma once

#include <string>

namespace parsium {
namespace mckeeman {
namespace builder {

class Characters {
public:
	std::string content;
};

inline
bool does_accept(const Characters& cs, char c) {
	return size(cs.content) > 0 && c == cs.content.front();
}

}}}
