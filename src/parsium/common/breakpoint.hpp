#pragma once

#if(defined(_MSC_VER))
	#include <Windows.h>

	#include <debugapi.h>
#endif

#include <utility>

namespace parsium {

void breakpoint();

inline
bool breakpoint_on_false(bool b) {
	if(!b) {
		breakpoint();
	}
	return b;
}

inline
void breakpoint()
#if(defined(_MSC_VER))
{
	__debugbreak();
}
#else
{
	// TODO: Clang, GCC.
}
#endif

}