#pragma once

#include <string_view>

namespace parsium {
namespace common {

class InputStream {
public:
	InputStream(std::string_view content)
		: content(content)
	{}

	bool is_done() const noexcept {
		return content.empty();
	}

	char peek() {
		return content.front();
	}

	void advance() {
		content.remove_prefix(1);
	}

// private:
	std::string_view content;
};

inline
char get(InputStream& is) {
	auto c = is.peek();
	is.advance();
	return c;
}

}
}