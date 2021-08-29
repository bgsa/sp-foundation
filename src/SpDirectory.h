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

#ifdef WINDOWS
	#define SP_DIRECTORY_OPENCL_SOURCE "resources\\gpgpu\\opencl\\source"
#else
	#define SP_DIRECTORY_OPENCL_SOURCE "resources/gpgpu/opencl/source"
#endif

#define SP_DIRECTORY_OPENCL_SOURCE_LENGTH 29
#define SP_DIRECTORY_MAX_LENGTH (512)

namespace NAMESPACE_FOUNDATION
{

	/// <summary>
	/// Get the current folder
	/// </summary>
	/// <param name="output">Current folder</param>
	/// <returns></returns>
	API_INTERFACE inline void currentDirectory(sp_char* output, const sp_size maxLength = SP_DIRECTORY_MAX_LENGTH)
	{
		GetCurrentDir(output, maxLength);
	}

	/// <summary>
	/// Create a new directory
	/// </summary>
	/// <param name="name">Directory name</param>
	/// <param name="nameLength">Directory name length</param>
	/// <returns>True it it was created</returns>
	API_INTERFACE inline sp_bool createDirectory(const sp_char* name, const sp_uint nameLength)
	{
#ifdef WINDOWS
		const sp_int errorCode = _mkdir(name);

		if (errorCode != 0)
		{
			std::cerr << "Error creating folder: '" << name << "' (" << errorCode << ") " << strerror(errno) << std::endl;
			return false;
		}
#else
		const sp_int errorCode = mkdir(name, 0777);

		if (errorCode == -1)
		{
			std::cerr << "Error :  " << strerror(errno) << std::endl;
			return false;
		}
#endif

		return true;
	}

	/// <summary>
	/// Check the directory exists
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	API_INTERFACE inline sp_bool directoryExists(const sp_char* name)
	{
#ifdef WINDOWS
		DWORD ftyp = GetFileAttributesA(name);
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!

		return false;    // this is not a directory!
#else
		struct stat info;

		sp_int statRC = stat(path, &info);
		if (statRC != 0)
		{
			if (errno == ENOENT) 
				return false; // something along the path does not exist

			if (errno == ENOTDIR) 
				return false; // something in path prefix is not a dir

			return false;
		}

		return info.st_mode & S_IFDIR;
#endif
	}

	/// <summary>
	/// Check the directory is empty
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	API_INTERFACE inline sp_bool isDirectoryEmpty(const sp_char* name)
	{
#ifdef WINDOWS
		sp_char pattern[SP_DIRECTORY_MAX_LENGTH];
		sp_size length = std::strlen(name);

		std::memcpy(pattern, name, (sizeof(sp_char) + 1u) * length);
		pattern[length] = END_OF_STRING;

		if (endsWith(pattern, SP_DIRECTORY_SEPARATOR_STR))
			strcat(pattern, "*");
		else
			if (endsWith(pattern, "/"))
				strcat(pattern, "*");
			else
			{
				strcat(pattern, SP_DIRECTORY_SEPARATOR_STR);
				strcat(pattern, "*");
			}

		WIN32_FIND_DATAA data;
		length = ZERO_SIZE;

		HANDLE hFind = FindFirstFileA(pattern, &data);
		sp_bool keep = true;

		while (hFind != INVALID_HANDLE_VALUE && keep)
		{
			if (std::strcmp(data.cFileName, ".") != 0 && std::strcmp(data.cFileName, "..") != 0)
			{
				FindClose(hFind);
				return false;
			}

			keep = FindNextFileA(hFind, &data);
		}

		FindClose(hFind);
		return true;
#else
		DIR* dir;
		struct dirent* dirEntry;

		if ((dir = opendir(name)) != nullptr)
		{
			const sp_bool hasEntry = (dirEntry = readdir(dir)) != nullptr;

			closedir(dir);

			return hasEntry;
		}
#endif
	}

	/// <summary>
	/// Add path to directory
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="path"></param>
	/// <returns></returns>
	API_INTERFACE inline void directoryAddPath(const sp_char* directory, const sp_size directoryLength, const sp_char* path, const sp_size pathLength, sp_char* output)
	{
		sp_size length = directoryLength;
		std::memcpy(output, directory, length);

		if (output[length - 1] != '/')
		{
#ifdef WINDOWS
			if (output[length - 1] != '\\')
#endif
			output[length++] = SP_DIRECTORY_SEPARATOR;
		}

		std::memcpy(&output[length], path, pathLength);
		output[length + pathLength] = END_OF_STRING;
	}

	/// <summary>
	/// Add path to directory
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="path"></param>
	/// <returns></returns>
	API_INTERFACE inline void directoryAddPath(sp_char* directory, const sp_size directoryLength, const sp_char* path, const sp_size pathLength)
	{
		sp_size length = directoryLength;

		if (directory[length] != '/')
		{
#ifdef WINDOWS
			if (directory[length] != '\\')
#endif
				directory[length++] = SP_DIRECTORY_SEPARATOR;
		}

		std::memcpy(&directory[length], path, pathLength);
		directory[length + pathLength] = END_OF_STRING;
	}

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
			sp_char pattern[SP_DIRECTORY_MAX_LENGTH];
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
			sp_char pattern[SP_DIRECTORY_MAX_LENGTH];
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
			DIR* dir;
			struct dirent* dirEntry;

			if ((dir = opendir(_name->data())) != nullptr) 
			{
				while ((dirEntry = readdir(dir)) != nullptr) {
					files.add(dirEntry->d_name);
				}

				closedir(dir);
			}
#endif
		}

		API_INTERFACE inline sp_bool create()
		{
			return createDirectory(_name->data(), (sp_uint)_name->length());
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