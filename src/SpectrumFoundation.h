#ifndef SPECTRUM_FOUNDATION_HEADER
#define SPECTRUM_FOUNDATION_HEADER

#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"
#endif

#include <cassert>
#include "StackMemoryAllocator.h"
#include "PoolMemoryAllocator.h"
#include "Log.hpp"



#endif // !SPECTRUM_FOUNDATION_HEADER