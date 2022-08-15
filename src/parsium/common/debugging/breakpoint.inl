#include "breakpoint.hpp"

#if(defined(_MSC_VER))
	#include <Windows.h>

	#include <debugapi.h>
#endif

#include <utility>

namespace parsium {

inline void breakpoint()
	#if(defined(_MSC_VER))
	{
		__debugbreak();
	}
	#else
	{
		// TODO: Clang, GCC.
	}
	#endif

inline auto breakpoint_on_false(bool b) -> bool {
	if(!b) {
		breakpoint();
	}
	return b;
}

}