#ifndef INPUT_DEVICE_HEADER
#define INPUT_DEVICE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class InputDevice
	{
	public:
		
		virtual void update(sp_longlong elapsedTime) = 0;

		virtual ~InputDevice() {}

	};
}

#endif // INPUT_DEVICE_HEADER