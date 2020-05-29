#ifndef SP_DIRECTORY_HEADER
#define SP_DIRECTORY_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#define SP_DIRECTORY_OPENCL_SOURCE "resources/gpgpu/opencl/source"

namespace NAMESPACE_FOUNDATION
{
	class SpDirectory :
		public Object
	{
	private:
		SpString* _name;

	public:

		API_INTERFACE SpDirectory()
		{
			_name = sp_mem_new(SpString)();
		}
		API_INTERFACE SpDirectory(const sp_uint length)
		{
			_name = sp_mem_new(SpString)(length);
		}
		API_INTERFACE SpDirectory(const sp_char* path)
		{
			_name = sp_mem_new(SpString)(path);
		}

		API_INTERFACE static SpDirectory* currentDirectory()
		{
			sp_char value[FILENAME_MAX];
			GetCurrentDir(value, FILENAME_MAX);

			SpDirectory* dir = sp_mem_new(SpDirectory)(FILENAME_MAX);
			dir->add(value);

			return dir;
		}

		API_INTERFACE SpString* name() const
		{
			return _name;
		}

		API_INTERFACE SpDirectory* add(const sp_char* path)
		{
			if (_name->length() != ZERO_UINT)
				_name->add(SP_DIRECTORY_SEPARATOR);

			_name->add(path);
			return this;
		}

		API_INTERFACE static SpString* buildPath(const SpString& path1, const SpString& path2)
		{
			SpString* newPath = sp_mem_new(SpString)(path1.length() + path2.length() + SP_DIRECTORY_SEPARATOR_LENGTH);
			newPath->append(path1);
			newPath->add(SP_DIRECTORY_SEPARATOR);
			newPath->add(path2);

			return newPath;
		}

		API_INTERFACE const sp_char* toString() override
		{
			return _name->data();
		}

		API_INTERFACE void dispose() override
		{
			if (_name != nullptr)
			{
				sp_mem_delete(_name, SpString);
				_name = nullptr;
			}
		}

		~SpDirectory()
		{
			dispose();
		}

	};
}

#endif // SP_DIRECTORY_HEADER