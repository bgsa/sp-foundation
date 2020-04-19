#include "RendererSize.h"

namespace NAMESPACE_FOUNDATION
{
	static RendererSize* instance = NULL;

	void RendererSize::init()
	{
		if (instance == NULL)
			instance = ALLOC_NEW(RendererSize);
	}

	RendererSize* RendererSize::getInstance()
	{
		return instance;
	}
}