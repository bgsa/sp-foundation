#ifndef SP_DYNAMIC_LIBRARY_HEADER
#define SP_DYNAMIC_LIBRARY_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpDynamicLibrary
	{
	private:

#ifdef WINDOWS
		HMODULE handler;
#else
		void* handler;
#endif
		sp_char _name[64];

#ifdef WINDOWS
		void getErrorMessage(const sp_char* filename, sp_char* message)
		{
			sp_int errorCode = GetLastError();

			switch (errorCode)
			{
			case 126:
			{
				strcat(message, "Library '");
				strcat(message, filename);
				strcat(message, "' not found");
				break;
			}
			default:
				break;
			}
		}
#endif

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		API_INTERFACE SpDynamicLibrary()
		{
			handler = nullptr;
		}

		/// <summary>
		/// Load a shared/dynamic library (.dll or .so), given the filename
		/// If the library is not in the path, a full filename has to be provided
		/// </summary>
		/// <param name="filename">Filename</param>
		/// <returns>void</returns>
		API_INTERFACE inline void load(const sp_char* filename)
		{
#ifdef WINDOWS
			handler = LoadLibraryA(filename);

			if (handler == NULL)
			{
				sp_char message[256];
				getErrorMessage(filename, message);
				std::cerr << message << std::endl;
				return;
			}
#else
			handler = dlopen(filename, RTLD_LAZY)); // RTLD_NOW | RTLD_LAZY
			if (handler == NULL)
			{
				std::cerr << dlerror() << std::endl;
				return;
			}
#endif
			filenameFromPath(filename, _name);
		}

		/// <summary>
		/// Unload the the current loaded library
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void unload()
		{
			if (handler == nullptr)
				return;

#ifdef WINDOWS
			if (!FreeLibrary(handler))
			{
				sp_char message[256];
				getErrorMessage("", message);
				std::cerr << message << std::endl;
			}
#else
			if (dlclose(handler) != NULL)
				std::cerr << dlerror() << std::endl;
#endif

			handler = nullptr;
		}

		/// <summary>
		/// Get a symbol from library
		/// </summary>
		/// <param name="symbolName">Name</param>
		/// <returns>Symbol reference</returns>
		API_INTERFACE void* symbol(const sp_char* symbolName)
		{
#ifdef WINDOWS
			return GetProcAddress(handler, symbolName);
#else
			dlerror(); /* clear error code */
			return dlsym(handler, symbolName);
#endif
		}

		/// <summary>
		/// Release all allocated resources
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void dispose()
		{
			unload();
		}

		~SpDynamicLibrary()
		{
			dispose();
		}

	};
}

#endif // SP_DYNAMIC_LIBRARY_HEADER