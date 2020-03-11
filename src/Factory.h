#ifndef FACTORY_HEADER
#define FACTORY_HEADER

#include "IFileManager.h"
#include "Log.hpp"

#ifdef ANDROID
	#include "FileManagerAndroid.h"
#endif
#ifdef WINDOWS
	#include "FileManagerWindows.h"
#endif
#ifdef LINUX
	#include "FileManagerLinux.h"
#endif

namespace NAMESPACE_FOUNDATION
{
	class Factory
	{
	public:

		static IFileManager * getFileManagerInstance()
		{
	#ifdef ANDROID
			return new FileManagerAndroid;
	#endif
	#ifdef WINDOWS
			return new FileManagerWindows;
	#endif
	#ifdef LINUX
			return new FileManagerLinux;
	#endif
		}

	};
}

#endif // FACTORY_HEADER