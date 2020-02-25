#ifndef I_FILE_HEADER
#define I_FILE_HEADER

#include "apollo.h"

class IFile 
{
public:

	//virtual void read(char* buffer, size_t size, size_t count = 1) = 0;
	virtual void read(void* buffer, sp_uint size, sp_uint count = 1) = 0;
	virtual void seek(sp_long offset) = 0;
	virtual void close() = 0;
	
	virtual ~IFile() {};

};

#endif // !I_FILE_HEADER