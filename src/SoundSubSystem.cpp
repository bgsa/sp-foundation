#include "SoundSubSystem.h"

/*
#ifdef WINDOWS

void SoundSubSystem::initOpenAL()
{
	const ALCchar* devicename = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(devicename);
	context = alcCreateContext(device, nullptr);

	alcMakeContextCurrent(context); // set active context

	//ALenum error = alGetError(); // clear Error Code
}

void SoundSubSystem::init() 
{
	initOpenAL();
}

void SoundSubSystem::setDefaultVolume(float volume) 
{
	defaultVolume = volume;
}

vector<string> SoundSubSystem::getDeviceList()
{
	ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	vector<string> deviceList;

	if (!enumeration)
		return deviceList;

	const ALCchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	const ALCchar *deviceName = devices, *next = devices + 1;
	size_t len = 0;

	while (deviceName && *deviceName != '\0' && next && *next != '\0')
	{
		deviceList.push_back(deviceName);

		len = strlen(deviceName);
		deviceName += (len + 1);
		next += (len + 2);
	}

	return deviceList;
}

SoundSubSystem::~SoundSubSystem()
{
	if (context != nullptr)
		alcDestroyContext(context);

	if (device != nullptr)
		alcCloseDevice(device);
}

#endif
*/