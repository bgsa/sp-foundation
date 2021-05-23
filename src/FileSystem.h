#ifndef FILE_SYSTEM_HEADER
#define FILE_SYSTEM_HEADER

#include "SpectrumFoundation.h"
#include "SpDirectory.h"

#define SP_FILE_MODE_BINARY std::ios::bin
#define SP_FILE_MODE_READ   std::ios::in
#define SP_FILE_MODE_WRITE  std::ios::out
#define SP_FILE_MODE_APPEND std::ios::out | std::ios::app
#define SP_FILE_MODE_TRUNC  std::ios::trunc // if the file is opened for output operationsand it already existed, its previous content is deletedand replaced by the new one.

#ifdef WINDOWS
	#include "FileWindows.h"
#elif defined(LINUX)
	#include "FileLinux.h"
#elif defined(OSX)
	#include "FileOSX.h"
#endif

#if defined(WINDOWS)
	#define SP_FILE FileWindows
#elif defined(LINUX)
	#define SP_FILE FileLinux
#elif defined(OSX)
	#define SP_FILE FileOSX
#endif

#endif // FILE_SYSTEM_HEADER