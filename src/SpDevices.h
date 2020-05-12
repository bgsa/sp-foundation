#ifndef SP_DEVICES_HEADER
#define SP_DEVICES_HEADER

#include "SpectrumFoundation.h"
#include "SpWindow.h"
#include "SpMouse.h"
#include "SpKeyboard.h"

namespace NAMESPACE_FOUNDATION
{
	class SpDevices
	{
	private:

		SpDevices()
		{
		}

	public:
		SpWindow* window;
		SpMouse* mouse;
		SpKeyboard* keyboard;

		API_INTERFACE static SpDevices* instance()
		{
			static SpDevices* _instance = sp_mem_new(SpDevices)();
			return _instance;
		}
	};
}

#endif // BASE_PLATFORM_HEADER
