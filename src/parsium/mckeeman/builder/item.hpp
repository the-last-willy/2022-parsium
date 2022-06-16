#pragma once

#include "parsium/mckeeman/builder/literal.hpp"
#include "parsium/mckeeman/builder/name.hpp"

#include <variant>

namespace parsium {
namespace mckeeman {
namespace builder {

class Item {
	std::variant<Literal, Name> item_;

public:
	Item(Name n)
	: item_(std::move(n))
	{}

	Item(Literal l)
	: item_(std::move(l))
	{}

	template<typename T>
	auto dispatch_to(T&& t) const -> decltype(auto);

	const Literal* literal_or(std::nullptr_t) const {
		return std::get_if<Literal>(&item_);
	}

	const Name* name_or(std::nullptr_t) const {
		return std::get_if<Name>(&item_);
	}
};

const Literal* literal_or(const Item& i, std::nullptr_t) {
	return i.literal_or(nullptr);
}

const Name* name_or(const Item& i, std::nullptr_t) {
	return i.name_or(nullptr);
}

}}}
