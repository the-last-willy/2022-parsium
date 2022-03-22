#pragma once

namespace parsium {
namespace common {

class InputStream {
public:
	InputStream(const char* first, const char* last)
		: first(first)
		, last(last)
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

private:
	const char* first;
	const char* last;
};

}
}