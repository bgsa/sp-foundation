#ifndef ASSERTIONS_HEADER
#define ASSERTIONS_HEADER

#include <cassert>

#ifdef DEBUG
	#define sp_assert(condition) assert(condition)
#else
	#define sp_assert(condition)
#endif

#endif // ASSERTIONS_HEADER