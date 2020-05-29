#ifndef FILE_SYSTEM_HEADER
#define FILE_SYSTEM_HEADER

#include "SpectrumFoundation.h"
#include "SpDirectory.h"

#ifdef WINDOWS
	#include "FileWindows.h"
#elif LINUX
	#include "FileLinux.h"
#elif OSX
	#include "FileOSX.h"
#endif

#ifdef WINDOWS
	#define SP_FILE FileWindows
#elif LINUX
	#define SP_FILE FileLinux
#elif OSX
	#define SP_FILE FileOSX
#endif

#endif // FILE_SYSTEM_HEADER