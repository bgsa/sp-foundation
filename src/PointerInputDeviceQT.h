#ifdef QT_ENABLED

#ifndef POINTER_INPUT_DEVICE_QT_HEADER
#define POINTER_INPUT_DEVICE_QT_HEADER

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include "SpectrumFoundation.h"
#include "PointerInputDevice.h"
#include <qwindow.h>
#include <qguiapplication.h>
#include <qevent.h>
#include <qscreen.h>

namespace NAMESPACE_FOUNDATION
{
	class PointerInputDeviceQT : public QObject, public PointerInputDevice
	{
		Q_OBJECT

	private:
		QWidget* window = nullptr;
		sp_float previousPosition[2] = {0.0f, 0.0f};

	public:
		API_INTERFACE void init(QWidget* window);
		API_INTERFACE void update(sp_longlong elapsedTime);

		API_INTERFACE void addHandler(PointerInputDeviceHandler* handler);
		API_INTERFACE void removeHandler(PointerInputDeviceHandler* handler);

		API_INTERFACE sp_bool eventFilter(QObject *object, QEvent *event);
	};
}

#endif // !POINTER_INPUT_DEVICE_QT_HEADER

#endif // QT_ENABLED
