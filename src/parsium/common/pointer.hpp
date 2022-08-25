#pragma once

#include <parsium/common/compiler/inlining_prologue.hpp>

namespace parsium {

/**
 * Nullable pointer.
 */
template<typename T>
class NP {
public:
	T* ptr_ = nullptr;

	NP() = default;

	NP(T* t)
	: ptr_(t)
	{}

	auto operator=(T* t) -> NP& {
		ptr_ = t;
		return *this;
	}

	ALWAYS_INLINED
	operator T*() const {
		return ptr_;
	}

	ALWAYS_INLINED
	auto operator->() const -> const T* {
		return ptr_;
	}

	ALWAYS_INLINED
	auto operator->() -> T* {
		return ptr_;
	}
};

/**
 * (Non-nullable) pointer.
 */
template<typename T>
class P {
public:
	T* ptr_;

	P() = delete;

	P(T& ptr)
	: ptr_(&ptr)
	{}

	P(decltype(nullptr)) = delete;

	auto operator=(T* ptr) -> P& {
		ptr_ = ptr;
		return *this;
	}

	ALWAYS_INLINED
	operator T*() const {
		return ptr_;
	}

	ALWAYS_INLINED
	auto operator->() const -> const T* {
		return ptr_;
	}

	ALWAYS_INLINED
	auto operator->() -> T* {
		return ptr_;
	}
};

}

#include <parsium/common/compiler/inlining_epilogue.hpp>
