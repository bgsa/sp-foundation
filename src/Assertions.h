#ifndef ASSERTIONS_HEADER
#define ASSERTIONS_HEADER

#ifdef DEBUG
	#include <cassert>
	#include <iostream>

	#define sp_assert(condition) std::cout << std::strerror(errno); assert(condition)
#else
	#define sp_assert(condition)
#endif

#endif // ASSERTIONS_HEADER