#ifndef DISPLAY_DEVICE_HEADER
#define DISPLAY_DEVICE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class DisplayDevice
	{
	private:
		int width;
		int height;

	protected:
		void setWidth(sp_int width);
		void setHeight(sp_int height);

	public:
		virtual sp_int getWidth() {
			return width;
		}

		virtual sp_int getHeight() {
			return height;
		}

		virtual void swapBuffer() {};

		virtual ~DisplayDevice() {}
	};
}}

#endif // ! DISPLAY_DEVICE_HEADER