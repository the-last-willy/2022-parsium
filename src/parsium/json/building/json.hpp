#pragma once

#include "parsium/json/building/element.hpp"

#include <parsium/common/exception/precondition_violation.hpp>
#include <parsium/common/tag/shallow.hpp>

#include <optional>
#include <type_traits>

namespace parsium {
namespace json {
namespace building {

template<typename T>
struct ElementCreator {
	template<typename U>
	auto operator()(U& u) -> T& {
		if constexpr(std::is_same_v<std::remove_reference_t<U>, T>) {
			return u;
		} else {
			throw PreconditionViolation();
		}
	}
};

class Json {
	std::optional<Element> element_;

public:
	auto is_valid(decltype(shallow)) const -> bool;

	auto element_or(decltype(nullptr)) const -> const Element* {
		if(element_) {
			return &*element_;
		} else {
			return nullptr;
		}
	}

	auto element_or(decltype(nullptr)) -> Element* {
		if(element_) {
			return &*element_;
		} else {
			return nullptr;
		}
	}

	template<typename T>
	auto create() -> T& {
		element_ = Element(T());
		return element_->dispatch_to(ElementCreator<T>());
	}
};

}}}
