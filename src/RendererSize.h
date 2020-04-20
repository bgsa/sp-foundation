#ifndef RENDERER_SIZE_HEADER
#define RENDERER_SIZE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
    class RendererSize
    {
    private:
		sp_float width = ZERO_FLOAT;
		sp_float height = ZERO_FLOAT;
        
        RendererSize()
        {
            ;
        }
        
    public:

        API_INTERFACE static void init();

        API_INTERFACE static RendererSize* getInstance();

        API_INTERFACE inline sp_float getWidth()
        {
            return width;
        }
        API_INTERFACE inline sp_float getHeight()
        {
            return height;
        }

        API_INTERFACE inline void resize(sp_float width, sp_float height)
        {
			this->width = width;
			this->height = height;
        }

    };
}

#endif // RENDERER_SIZE_HEADER
