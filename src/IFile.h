#ifndef I_FILE_HEADER
#define I_FILE_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class IFile 
	{
	public:

		API_INTERFACE virtual void open(const sp_char* filename, std::ios_base::openmode mode) = 0;

		API_INTERFACE virtual sp_bool isOpened() = 0;

		API_INTERFACE virtual sp_size length() = 0;

		API_INTERFACE virtual sp_bool isAtEnd() = 0;

		API_INTERFACE virtual void seek(const sp_size position, std::ios_base::seekdir direction = std::ios::cur) = 0;

		API_INTERFACE virtual void read(sp_char* buffer, sp_uint size) = 0;

		API_INTERFACE virtual void write(const sp_char* buffer) = 0;

		API_INTERFACE virtual SpString* readTextFile(const sp_char* filename) = 0;

		API_INTERFACE virtual void close() = 0;

	};
}

#endif // !I_FILE_HEADER
