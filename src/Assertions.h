#ifndef ASSERTIONS_HEADER
#define ASSERTIONS_HEADER

#ifdef DEBUG
	#include <cassert>
	#include <iostream>

	#define sp_assert(condition, message)                                 \
		if (!(condition))                                                 \
		{                                                                 \
			std::cout << message << ": " << std::strerror(errno);         \
			std::cout << "File: " << __FILE__ << " (line " << __LINE__ << ")";  \
			std::cout << END_OF_LINE;                                     \
		}                                                                 \
		assert(condition)
			
#else
	#define sp_assert(condition)
#endif

#endif // ASSERTIONS_HEADER