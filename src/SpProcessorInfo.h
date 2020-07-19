#ifndef SP_PROCESSOR_INFO_HEADER
#define SP_PROCESSOR_INFO_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpProcessorInfo
	{
	public:

		SpString* name;
		sp_float frequency;
		sp_uint cores;
		sp_uint logicalProcessors;

	};
}

#endif // SP_PROCESSOR_INFO_HEADER