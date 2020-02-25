#ifndef RENDERER_SIZE_HEADER
#define RENDERER_SIZE_HEADER

#include "apollo.h"

class RendererSize
{
private:
    sp_int width = 0;
    sp_int height = 0;

    static RendererSize* instance;

    RendererSize()
    {
        ;
    }
	
public:

    API_INTERFACE static void init()
    {
        instance = ALLOC_NEW(RendererSize);
    }

    API_INTERFACE static RendererSize* getInstance()
    {
        return instance;
    }

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
