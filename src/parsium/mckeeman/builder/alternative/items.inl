#pragma once

#include "parsium/mckeeman/builder/alternative.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

auto Alternative::items() const -> const std::deque<Item>& {
	return items_;
}

auto Alternative::items() -> std::deque<Item>& {
	return items_;
}

}}}
