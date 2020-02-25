#pragma once

#include "apollo.h"
#include "ColorRGB.h"

class Image 
{
private:
	
protected:
	sp_int width;
	sp_int height;
	sp_uchar* data;
	sp_uint colorFormat;
	
public:
    Image();   
	virtual ~Image();
	
	sp_int getWidth();
	sp_int getHeight();
	sp_uchar* getData();
	sp_uint getColorFormat();
	virtual ColorRGBc getPixelRGB(sp_int x, sp_int y) = 0;
};
