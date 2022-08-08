#pragma once

#include <string>

namespace parsium {

inline std::string escaped(const std::string& s) {
	auto ret = std::string();
	for(auto c : s) {
		switch(c) {
			case '"': {
				ret += "\\\"";
				break;
			}
			case '\n': {
				ret += "\\n";
				break;
			}
			case '\r': {
				ret += "\\r";
				break;
			}
			default: {
				ret += c;
			}
		}
	}
	return ret;
}

}