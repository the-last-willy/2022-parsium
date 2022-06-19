#pragma once

#include "parsium/mckeeman/builder/characters/does_accept.hpp"
#include "parsium/mckeeman/builder/literal.hpp"
#include "parsium/mckeeman/builder/literal/dispatch_to.inl"
#include "parsium/mckeeman/builder/range_exclude/does_accept.hpp"
#include "parsium/mckeeman/builder/singleton/does_accept.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

// Error handling ?
inline
bool does_accept(const Literal& l, std::size_t index, char c) {
	return l.dispatch_to([=](auto a) -> bool {
		return does_accept(a, index, c); });
}

}}}
