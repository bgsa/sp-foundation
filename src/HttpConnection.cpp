/*
#include "HttpConnection.h"

#ifdef WINDOWS

size_t write_data_bytes(void* content, size_t size, size_t nmemb, DownloadData* data)
{
	size_t realsize = size * nmemb;

	data->content = realloc(data->content, data->size + realsize + 1);

	memcpy(&((char*)data->content)[data->size], content, realsize);

	data->size += realsize;

	((char*)data->content)[data->size] = 0;

	return realsize;
}

string HttpConnection::urlEncode(string content)
{
	char* output = curl_easy_escape(curl, content.c_str(), (int) content.length());
		
	string result = string(output);
	curl_free(output);

	return result;
}

void HttpConnection::setUrl(string url)
{
	setOption(CURLOPT_URL, (void*) url.c_str() );
}

void HttpConnection::setOption(CURLoption option, void* value) 
{
	curl_easy_setopt(curl, option, value);
}

void HttpConnection::setPutMethod() 
{
	setOption(CURLOPT_PUT, (void*) true);
}

void HttpConnection::setDeleteMethod()
{
	setOption(CURLOPT_CUSTOMREQUEST, (void*)"DELETE");
}

HttpOperationResult* HttpConnection::execute(const string& url)
{
	HttpOperationResult* result = new HttpOperationResult;

	string urlLowerCase = StringHelper::toLowerCase(url);

	bool isHttpsRequest = StringHelper::startWith(urlLowerCase, "https");
	if (isHttpsRequest)
	{
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	}

	setUrl(url);

	setOption(CURLOPT_FOLLOWLOCATION, (void*)1L); // follow the url in case of redirect redirection 
	setOption(CURLOPT_NOSIGNAL, (void*)1); //Prevent "longjmp causes uninitialized stack frame" bug
	setOption(CURLOPT_ACCEPT_ENCODING, (void*) "deflate");
	setOption(CURLOPT_WRITEFUNCTION, (void*)write_data_bytes);
	setOption(CURLOPT_WRITEDATA, &result->data);

	if (headers != nullptr)
		setOption(CURLOPT_HTTPHEADER, headers);

	CURLcode cUrlCode = curl_easy_perform(curl);  // Perform the request, res will get the return code 

	if (cUrlCode != CURLE_OK)  // Check for errors 
	{
		const char* errorMessage = curl_easy_strerror(cUrlCode);
		fprintf(stderr, "curl_easy_perform() failed: %s\n", errorMessage);
	}

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result->httpStatusCode);
	curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &result->totalSize);
	curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &result->downloadTime);
	curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &result->connectionSpeed);

	return result;
}

HttpOperationResult* executeAsync(HttpConnection* httpConnection, const string& url)
{
	return httpConnection->execute(url);
}

HttpOperationResult* HttpConnection::get(const string& url)
{	
	return execute(url);
}

HttpOperationResult* HttpConnection::download(const string& url)
{
	return execute(url);
}

HttpOperationResult* HttpConnection::post(const string& url, map<string, string> parameters)
{
	string parametersAsString = "";

	for (map<string, string>::iterator parameter = parameters.begin(); parameter != parameters.end(); ++parameter)
		parametersAsString += parameter->first + "=" + parameter->second + "&";

	if (parametersAsString.length() > 0)
		parametersAsString = parametersAsString.substr(0, parametersAsString.length() - 1);

	setOption(CURLOPT_POSTFIELDS, (void*)parametersAsString.c_str());
	setOption(CURLOPT_POSTFIELDSIZE, (void*)parametersAsString.length());

	return execute(url);
}

future<HttpOperationResult*> HttpConnection::getAsync(const string& url)
{
	future<HttpOperationResult*> futureObj = async(executeAsync, this, url);

	return futureObj;
}

void HttpConnection::setHeader(string name, string value) 
{
	string content = name + ": " + value;
	headers = curl_slist_append(headers, content.c_str());
}

void HttpConnection::setUserAgent(string userAgent)
{
	setOption(CURLOPT_USERAGENT, (void*) userAgent.c_str());
}

void HttpConnection::enableDebugMode() 
{
	setOption(CURLOPT_VERBOSE, (void*) 1 );
}

void HttpConnection::reset()
{
	curl_easy_reset(curl);
}

HttpConnection::HttpConnection()
{
	if (curl == nullptr)
		curl = curl_easy_init();
}

void HttpConnection::close() 
{
	if (curl != nullptr)
		curl_easy_cleanup(curl);
}

HttpConnection::~HttpConnection()
{
	close();
}


#endif
*/