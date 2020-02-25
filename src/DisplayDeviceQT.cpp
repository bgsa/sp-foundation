#ifdef QT_ENABLED

#include "DisplayDeviceQT.h"

DisplayDeviceQT::DisplayDeviceQT()
{
}

void DisplayDeviceQT::init(QWidget* window) 
{
	this->window = window;

	QRect screenSize = QGuiApplication::primaryScreen()->geometry();

	setWidth(screenSize.width());
	setHeight(screenSize.height());
}

void DisplayDeviceQT::swapBuffer() 
{
}

#endif