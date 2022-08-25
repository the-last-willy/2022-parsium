// No inclusion guard.

#if(defined(_MSC_VER))
	#define ALWAYS_INLINED __forceinline
#else
	#define ALWAYS_INLINED
#endif
