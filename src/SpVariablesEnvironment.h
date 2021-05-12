#ifndef SP_VARIABLES_ENVIRONMENT_HEADER
#define SP_VARIABLES_ENVIRONMENT_HEADER

#include "SpectrumFoundation.h"
#include <stdlib.h>

namespace NAMESPACE_FOUNDATION
{

#ifdef WINDOWS
	API_INTERFACE inline sp_bool getVariableEnvirontmentLength(const sp_char* name, sp_uint& length)
	{
		return getenv_s(&length, NULL, 0, name);
	}

	API_INTERFACE inline sp_bool getVariableEnvirontmentValue(const sp_char* name, sp_char* value)
	{
		sp_uint len;
		return getenv_s(&len, NULL, 0, name);
	}

	API_INTERFACE inline void setVariableEnvirontment(const sp_char* name, const sp_char* value)
	{
		_putenv_s(name, value);
	}
#endif

#if defined(LINUX) || defined(OSX)
	API_INTERFACE inline void setVariableEnvirontment(const sp_char* name, const sp_char* value)
	{
		setenv(name, value, true);
	}
	API_INTERFACE inline sp_bool getVariableEnvirontmentValue(const sp_char* name, sp_char* value)
	{
		sp_char* temp = getenv(name);
		strcpy(value, temp);
		delete temp;

		return true;
	}
#endif


}

#endif // SP_VARIABLES_ENVIRONMENT_HEADER