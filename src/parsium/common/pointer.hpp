#pragma once

namespace parsium {

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

	operator T*() const {
		return ptr_;
	}
};

template<typename T>
class P {
public:
	T* ptr_;

	operator T*() const {
		return ptr_;
	}
};

}