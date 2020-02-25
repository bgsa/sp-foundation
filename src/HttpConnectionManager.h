/*
#pragma once

#include "HttpConnection.h"

#ifdef WINDOWS

class HttpConnectionManager 
{
private:
	HttpConnectionManager() {}
	
public:

	static HttpConnectionManager* getInstance() 
	{
		static HttpConnectionManager* instance;

		if (instance == nullptr)
		{
			instance = new HttpConnectionManager;
			curl_global_init(CURL_GLOBAL_ALL);
		}

		return instance;
	}

	HttpConnection* createConnection();
	
	~HttpConnectionManager();
};

#endif
*/