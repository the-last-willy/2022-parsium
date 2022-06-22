#pragma once

#include "parsium/json/building/array.hpp"
#include "parsium/json/building/number.hpp"
#include "parsium/json/building/object.hpp"
#include "parsium/json/building/string.hpp"

#include <parsium/common/tag/shallow.hpp>

#include <variant>

namespace parsium {
namespace json {
namespace building {

class Element {
	// std::variant<std::monostate, Array, Number, Object, String> content_;
	std::variant<Array, Number, Object, String> content_;

public:
	Element() = default;

	Element(Array a)
	: content_(std::move(a))
	{}

	Element(Number n)
	: content_(std::move(n))
	{}

	Element(Object&& o)
	: content_(std::move(o))
	{}

	Element(String s)
	: content_(std::move(s))
	{}

	auto is_valid(decltype(shallow)) const -> bool;

	template<typename Visitor>
	auto dispatch_to(Visitor&&) const -> decltype(auto);
	template<typename Visitor>
	auto dispatch_to(Visitor&&) -> decltype(auto);

	template<typename T>
	auto construct() -> T& {
		return content_.emplace<T>();
	}
};

template<typename F>
decltype(auto) Element::dispatch_to(F&& f) const {
	return std::visit(std::forward<F>(f), content_);
}

template<typename F>
decltype(auto) Element::dispatch_to(F&& f) {
	return std::visit(std::forward<F>(f), content_);
}

}}}
