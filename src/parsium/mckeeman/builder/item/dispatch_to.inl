#pragma once

#include "parsium/mckeeman/builder/item.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

template<typename T>
decltype(auto) Item::dispatch_to(T&& t) const {
	return std::visit(std::forward<T>(t), item_);
}

}}}
