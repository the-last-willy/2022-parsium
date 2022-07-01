#pragma once

namespace parsium::inline common {

/**
 * May you find it in yourself to forgive me for writing this.
 */
template<typename T>
class FakePtr {
	T data_;

public:
	FakePtr() = delete;

	FakePtr(const T& data)
	: data_(data)
	{}

	FakePtr(T&& data)
	: data_(std::move(data))
	{}

	FakePtr(const FakePtr&) = delete;
	FakePtr(FakePtr&&) = default;

	FakePtr& operator=(const FakePtr&) = delete;
	FakePtr& operator=(FakePtr&&) = default;

	auto operator*() -> T& {
		return data_;
	}

	auto operator->() -> T* {
		return &data_;
	}
};

}
