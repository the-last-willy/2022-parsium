#pragma once

#include "parsium/mckeeman/builder/literal.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

template<typename T>
decltype(auto) Literal::dispatch_to(T&& t) const {
	return std::visit(std::forward<T>(t), content);
}

}}}
