#pragma once

#include "parsium/mckeeman/builder/characters/character_count.hpp"
#include "parsium/mckeeman/builder/literal.hpp"
#include "parsium/mckeeman/builder/literal/dispatch_to.inl"
#include "parsium/mckeeman/builder/range_exclude/character_count.hpp"
#include "parsium/mckeeman/builder/singleton/character_count.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

inline
std::size_t character_count(const Literal& l) {
	return l.dispatch_to([](auto a) -> std::size_t {
		return character_count(a); });
}

}}}
