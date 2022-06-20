#pragma once

#include "parsium/json/building/array.hpp"
#include "parsium/json/building/number.hpp"
#include "parsium/json/building/object.hpp"
#include "parsium/json/building/string.hpp"

#include <variant>

namespace parsium {
namespace json {
namespace building {

class Element {
	std::variant<Array, Number, Object, String> content_;

public:
	Element(Array a)
	: content_(std::move(a))
	{}

	Element(Number n)
		: content_(std::move(n))
	{}

	Element(Object o)
		: content_(std::move(o))
	{}

	Element(String s)
		: content_(std::move(s))
	{}

	template<typename F>
	auto dispatch_to(F&&) const -> decltype(auto);
	template<typename F>
	auto dispatch_to(F&&) -> decltype(auto);
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
