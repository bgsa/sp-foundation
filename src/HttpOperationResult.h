#ifndef HTTP_OPERATION_RESULT_HEADER
#define HTTP_OPERATION_RESULT_HEADER

#include "apollo.h"
#include <iostream>

struct DownloadData
{
	void* content = malloc(1);
	sp_uint size = 0;
};

class HttpOperationResult
{
public:
	sp_long httpStatusCode;
	DownloadData data;

	sp_double connectionSpeed;
	sp_double downloadTime;
	sp_double totalSize;

	/*
	~HttpOperationResult();
	*/
};

#endif // !HTTP_OPERATION_RESULT_HEADER