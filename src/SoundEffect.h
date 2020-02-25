#pragma once

/*
#ifdef WINDOWS

#include <OPENAL/al.h>
#include <OPENAL/alc.h>

#include "IFileManager.h"
#include "Factory.h"

#pragma pack(push, 1)
struct WavHeader
{
	sp_uchar RIFF[4];
	sp_uint Size;
	sp_uchar WAVE[4];
	sp_uchar FMT[4];
	sp_uint SizeFmt;
	sp_ushort FormatTag;
	sp_ushort Channels;
	sp_uint SampleRate;
	sp_uint AvgBytesPerSec;
	sp_ushort nBlockAlign;
	sp_ushort nBitsperSample;
	sp_uchar Reserved[4];
	sp_uint DataSize;
};
#pragma pack(pop)

#define DEFAULT_VOLUME 1.0f

class SoundEffect
{
private:
	ALuint sourceID;
	ALuint bufferID;
		
	ALvoid* data;
	sp_uint dataSize;
	ALsizei frequence = 22050;
	ALenum format;

	void loadFile(string filename);
	ALenum getFormat(WavHeader header);

public:
	void init(std::string filename);
	
	int getState();

	sp_float getVolume();
	void setVolume(float volume);

	sp_float getPitch();
	void setPitch(sp_float pitch);

	sp_bool isLooping();
	void setLooping(sp_bool inLooping);		

	sp_bool isPlaying();
	sp_bool isStopped();
	sp_bool isPaused();

	void play();	
	void pause();
	void stop();

	~SoundEffect();
};

#endif
*/