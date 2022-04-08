#pragma once

#include <string>

namespace parsium {
namespace common {

class InputStream {
public:
	InputStream(const char* first, const char* last)
		: first(first)
		, last(last)
	{}

	InputStream(const std::string& s)
	: InputStream(s.c_str(), s.c_str() + size(s))
	{}

	bool is_done() const noexcept {
		return first == last;
	}

	char peek() {
		return *first;
	}

	void advance() {
		first++;
	}

// private:
	const char* first;
	const char* last;
};

inline
char get(InputStream& is) {
	auto c = is.peek();
	is.advance();
	return c;
}

}
}