#ifndef INPUT_DEVICE_HEADER
#define INPUT_DEVICE_HEADER

#include "apollo.h"

class InputDevice
{
public:
	
	virtual void update(sp_longlong elapsedTime) = 0;

	virtual ~InputDevice() {}

};

#endif // INPUT_DEVICE_HEADER