#ifndef SP_DIRECTORY_HEADER
#define SP_DIRECTORY_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"
#include "SpText.h"

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
    #include <sys/stat.h>
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

		API_INTERFACE static void buildPath(const sp_char* path1, const sp_char* path2, sp_char* output)
		{
			sp_size length = std::strlen(path1);
			std::memcpy(output, path1, sizeof(sp_char) * length);

			output[length++] = SP_DIRECTORY_SEPARATOR;

			const sp_size length2 = std::strlen(path2);
			std::memcpy(&output[length], path2, sizeof(sp_char) * length2);
			output[length + length2] = END_OF_STRING;
		}

		API_INTERFACE static void directoryFromFile(const sp_char* filename, sp_char* directory)
		{
			sp_size filenameLength = std::strlen(filename);

			for (sp_size i = filenameLength - ONE_SIZE; i > ZERO_SIZE; i--)
			{
				if (filename[i] == SP_DIRECTORY_SEPARATOR || filename[i] == '/')
				{
					std::memcpy(directory, filename, sizeof(sp_char) * i);
					directory[i] = END_OF_STRING;
					return;
				}
			}
		}

		API_INTERFACE inline void files(sp_char* files)
		{
#ifdef WINDOWS
#define isDirectory(win32Data) (win32Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			sp_char pattern[512];
			sp_size length = std::strlen(_name->data());

			std::memcpy(pattern, _name->data(), (sizeof(sp_char) + 1u) * length);
			pattern[length] = END_OF_STRING;

			strcat(pattern, "\\*");

			WIN32_FIND_DATAA data;
			HANDLE hFind;
			length = ZERO_SIZE;

			if ((hFind = FindFirstFileA(pattern, &data)) != INVALID_HANDLE_VALUE) 
			{
				do 
				{
					if (isDirectory(data))
						continue;

					sp_size strLength = std::strlen(data.cFileName);

					std::memcpy(&files[length], data.cFileName, (sizeof(sp_char) + 1) * strLength);
					length += strLength;
					files[length++] = END_OF_LINE;
				} 
				while (FindNextFileA(hFind, &data) != 0);

				FindClose(hFind);

				if (length == ZERO_SIZE)
					length++;

				files[length - ONE_SIZE] = END_OF_STRING;
			}
#undef isDirectory
#else
#endif
			/*
			DIR* dir; 
			struct dirent* diread;

			if ((dir = opendir(_name->data())) != nullptr) {
				while ((diread = readdir(dir)) != nullptr) {
					files.add(diread->d_name);
				}
				closedir(dir);
			}
			else 
			{
				perror("opendir");
				return EXIT_FAILURE;
			}
			*/
		}

		API_INTERFACE inline void subdirectories(sp_char* directories)
		{
#ifdef WINDOWS
#define isDirectory(win32Data) (win32Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			sp_char pattern[512];
			sp_size length = std::strlen(_name->data());

			std::memcpy(pattern, _name->data(), (sizeof(sp_char) + 1u) * length);
			pattern[length] = END_OF_STRING;

			strcat(pattern, "\\*");

			WIN32_FIND_DATAA data;
			HANDLE hFind;
			length = ZERO_SIZE;

			if ((hFind = FindFirstFileA(pattern, &data)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (!isDirectory(data))
						continue;

					sp_size strLength = std::strlen(data.cFileName);

					std::memcpy(&directories[length], data.cFileName, (sizeof(sp_char) + 1) * strLength);
					length += strLength;
					directories[length++] = END_OF_LINE;
				} 				while (FindNextFileA(hFind, &data) != 0);

				FindClose(hFind);

				if (length == ZERO_SIZE)
					length++;

				directories[length - ONE_SIZE] = END_OF_STRING;
			}
#undef isDirectory
#else
#endif
			/*
			DIR* dir;
			struct dirent* diread;

			if ((dir = opendir(_name->data())) != nullptr) {
				while ((diread = readdir(dir)) != nullptr) {
					files.add(diread->d_name);
				}
				closedir(dir);
			}
			else
			{
				perror("opendir");
				return EXIT_FAILURE;
			}
			*/
		}

		API_INTERFACE inline sp_bool create()
		{
#ifdef WINDOWS
			const sp_int errorCode = _mkdir(_name->data());

			if (errorCode != 0)
			{
				std::cerr << "Error creating folder: '" << _name->data() << "' (" << errorCode << ") " << strerror(errno) << std::endl;
				return false;
			}
#else
			const sp_int errorCode = mkdir(_name->data(), 0777);

			if (errorCode == -1)
			{
				std::cerr << "Error :  " << strerror(errno) << std::endl;
				return false;
			}
#endif
			return true;
		}

		API_INTERFACE void operator=(const sp_char* path) 
		{
			dispose();
			_name = sp_mem_new(SpString)(path);
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

	API_INTERFACE inline void filenameFromPath(const sp_char* path, sp_char* filename)
	{
		sp_size pathLength = std::strlen(path);

		for (sp_size i = pathLength - ONE_SIZE; i > ZERO_SIZE; i--)
		{
			if (path[i] == SP_DIRECTORY_SEPARATOR)
			{
				std::memcpy(filename, &path[i + ONE_SIZE], sizeof(sp_char) * (pathLength - i - ONE_SIZE));
				filename[pathLength - i - ONE_SIZE] = END_OF_STRING;
				return;
			}
		}
	}
}

#endif // SP_DIRECTORY_HEADER