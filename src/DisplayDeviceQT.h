#ifdef QT_ENABLED

#ifndef DISPLAY_DEVICE_QT_HEADER
#define DISPLAY_DEVICE_QT_HEADER

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include "SpectrumFoundation.h"
#include "DisplayDevice.h"
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>

class DisplayDeviceQT : public QObject, public DisplayDevice
{
	Q_OBJECT

private:
	QWidget* window;

public:
	API_INTERFACE DisplayDeviceQT();

	API_INTERFACE void init(QWidget* window);
	API_INTERFACE void swapBuffer() override;
};

#endif !DISPLAY_DEVICE_QT_HEADER

#endif // !QT_ENABLED