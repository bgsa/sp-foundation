/*

#include "HttpConnectionManager.h"

#ifdef WINDOWS

HttpConnection* HttpConnectionManager::createConnection() 
{
	HttpConnection* httpConnection = new HttpConnection;

	return httpConnection;
}

HttpConnectionManager::~HttpConnectionManager()
{
	curl_global_cleanup();
}

#endif
*/