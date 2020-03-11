/*
#ifndef NETWORK_SUBSYSTEM_HEADER
#define NETWORK_SUBSYSTEM_HEADER

#include "ISubSystem.h"
#include "HttpConnectionManager.h"

#ifdef WINDOWS

class NetworkSubSystem : public ISubSystem
{
private:
	HttpConnectionManager* httpConnectionManager;

public:
	void init();

	HttpConnection* getHttpConnection();

	~NetworkSubSystem();
};

#endif

#endif // NETWORK_SUBSYSTEM_HEADER
*/