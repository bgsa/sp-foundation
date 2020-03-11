#ifdef QT_ENABLED

#ifndef WINDOW_INPUT_DEVICE_QT_HEADER
#define WINDOW_INPUT_DEVICE_QT_HEADER

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include "SpectrumFoundation.h"
#include "WindowInputDevice.h"
#include <qwindow.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qevent.h>

namespace NAMESPACE_FOUNDATION
{
	class WindowInputDeviceQT : public QObject, public WindowInputDevice
	{
		Q_OBJECT

	private:
		QWidget* window;
		std::vector<WindowInputDeviceHandler*> handlers;

	public:

		API_INTERFACE static WindowInputDeviceQT* getInstance();

		API_INTERFACE void init(QWidget* window);
		API_INTERFACE void update(sp_longlong elapsedTime);

		API_INTERFACE void show();
		API_INTERFACE void hide();
		API_INTERFACE void move(sp_int previousPosition[2], sp_int newPosition[2]);
		API_INTERFACE void resize(sp_int width, sp_int height);
		API_INTERFACE void close();
		API_INTERFACE void maximize();
		API_INTERFACE void fullscreen();
		API_INTERFACE void focusIn();
		API_INTERFACE void focusOut();

		API_INTERFACE void addHandler(WindowInputDeviceHandler* handler);
		API_INTERFACE void removeHandler(WindowInputDeviceHandler* handler);

		API_INTERFACE sp_bool eventFilter(QObject *object, QEvent *event);

	};
}

#endif // !WINDOW_INPUT_DEVICE_QT_HEADER

#endif // QT_ENABLED