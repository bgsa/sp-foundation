#include "RendererSize.h"

static RendererSize* instance;

void RendererSize::init()
{
	instance = ALLOC_NEW(RendererSize);
}

RendererSize* RendererSize::getInstance()
{
	return instance;
}