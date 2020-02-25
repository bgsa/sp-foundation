/*
#pragma once

#ifdef WINDOWS

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <thread>
#include <future>

#include <curl/curl.h>
#include <curl/easy.h>

#include "HttpOperationResult.h"
#include "StringHelper.h"

using namespace std;

class HttpConnectionManager;

class HttpConnection
{
	friend class HttpConnectionManager;

private:
	void* curl;
	struct curl_slist *headers = NULL;

	HttpConnection();
		
public:
	string urlEncode(string content);

	void setOption(CURLoption option, void* value);
	void setUrl(string url);
	void setHeader(string name, string value);
	void setUserAgent(string userAgent);
	void setPutMethod();
	void setDeleteMethod();
	
	HttpOperationResult* execute(const string& url);
	HttpOperationResult* get(const string& url);
	future<HttpOperationResult*> getAsync(const string& url);
	HttpOperationResult* post(const string& url, map<string, string> parameters);
	HttpOperationResult* download(const string& url);

	void enableDebugMode();
	void reset();
	void close();

	~HttpConnection();
};


#endif
*/