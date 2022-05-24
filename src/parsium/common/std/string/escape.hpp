#pragma once

#include <string>

namespace parsium {

std::string escaped(std::string str) {
	auto escaped = std::string();
	for(auto c : str) {
		switch(c) {
			case '\n': {
				escaped += "\\n";
			} break;
			case '\r': {
				escaped += "\\r";
			} break;
			case '\t': {
				escaped += "\\t";
			} break;
			case '\\': {
				escaped += "\\\\";
			} break;
			default: {
				escaped += c;
			}
		}
	}
	return escaped;
}

}
