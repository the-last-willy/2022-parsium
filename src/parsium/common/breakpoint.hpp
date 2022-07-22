#pragma once

#if(defined(_MSC_VER))
	#include <Windows.h>

	#include <debugapi.h>
#endif

#include <utility>

namespace parsium {

void breakpoint();

template<typename T>
T&& break_on_false(T&& t) {
	if(!static_cast<bool>(std::forward<T>(t))) {
		breakpoint();
	}
	return std::forward<T>(t);
}

inline
void breakpoint()
#if(defined(_MSC_VER))
{
	__debugbreak();
}
#else
{}
#endif

}