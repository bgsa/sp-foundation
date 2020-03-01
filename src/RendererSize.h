#ifndef RENDERER_SIZE_HEADER
#define RENDERER_SIZE_HEADER

#include "SpectrumFoundation.h"

class RendererSize
{
private:
    sp_int width = 0;
    sp_int height = 0;
	
    RendererSize()
    {
        ;
    }
	
public:

	API_INTERFACE static void init();

	API_INTERFACE static RendererSize* getInstance();

    API_INTERFACE sp_int getWidth()
    {
        return width;
    }
    API_INTERFACE sp_int getHeight()
    {
        return height;
    }

	API_INTERFACE void resize(sp_int newWidth, sp_int newHeight)
    {
        this->width = newWidth;
        this->height = newHeight;
    }

};

#endif // RENDERER_SIZE_HEADER
