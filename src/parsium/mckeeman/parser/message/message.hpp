#pragma once

#include "parsium/mckeeman/name.hpp"

#include <variant>

namespace parsium {
namespace mckeeman {

enum class ParserAction {
	abort,
	consume,
	enter,
	exit
};

struct ParserMessage {
	ParserAction action;
	std::variant<std::monostate, const Name*, char> content;
};

inline
const Name* name_or(const ParserMessage& pm) {
	auto result = std::get_if<const Name*>(&pm.content);
	if(result) {
		return *result;
	} else {
		return nullptr;
	}
}

inline
const char* symbol_or(const ParserMessage& pm) {
	return std::get_if<char>(&pm.content);
}

}}
