#ifdef QT_ENABLED

#ifndef KEYBOARD_INPUT_DEVICE_QT_HEADER
#define KEYBOARD_INPUT_DEVICE_QT_HEADER

#ifdef Q_COMPILER_CONSTEXPR
	#undef Q_COMPILER_CONSTEXPR
#endif

#include <algorithm>
#include "apollo.h"
#include "KeyboardInputDevice.h"
#include <qguiapplication.h>
#include <qevent.h>
#include <qobject.h>

class KeyboardInputDeviceQT : public QObject, public KeyboardInputDevice
{
	Q_OBJECT

private:
	QWidget* window = nullptr;
	std::vector<KeyboardInputDeviceHandler*> handlersKeyboard;

public:
	API_INTERFACE void init(QWidget* window);
	API_INTERFACE void update(sp_longlong elapsedTime);

	API_INTERFACE sp_bool isKeyPressed(sp_int virtualKey);

	API_INTERFACE void addHandler(KeyboardInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(KeyboardInputDeviceHandler* handler);

	API_INTERFACE sp_bool eventFilter(QObject *object, QEvent *event);

};

#endif // !KEYBOARD_INPUT_DEVICE_QT_HEADER

#endif // QT_ENABLED
