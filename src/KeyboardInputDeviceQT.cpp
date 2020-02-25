#ifdef QT_ENABLED

#include "KeyboardInputDeviceQT.h"

void KeyboardInputDeviceQT::init(QWidget* window)
{
	this->window = window;
	QGuiApplication::instance()->installEventFilter(this);
}

void KeyboardInputDeviceQT::update(sp_longlong elapsedTime) 
{

}

bool KeyboardInputDeviceQT::isKeyPressed(sp_int virtualKey)
{
	//QK
	//QGuiApplication::keyboardModifiers().
	//QGuiApplication::queryKeyboardModifiers().testFlag(Qt::KeyboardModifier::)
	//QKeyEvent *event = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
	return false;
}

void KeyboardInputDeviceQT::addHandler(KeyboardInputDeviceHandler* handler)
{
	handler->init(nullptr);
	handlersKeyboard.push_back(handler);
}

void KeyboardInputDeviceQT::removeHandler(KeyboardInputDeviceHandler* handler)
{
	std::vector<KeyboardInputDeviceHandler*>::iterator item = std::find(handlersKeyboard.begin(), handlersKeyboard.end(), handler);

	if (item != handlersKeyboard.end())
		handlersKeyboard.erase(item);
}

bool KeyboardInputDeviceQT::eventFilter(QObject* object, QEvent *event)
{
	QKeyEvent *keyEvent = nullptr;

	switch (event->type())
	{
	case QEvent::KeyPress:
		keyEvent = static_cast<QKeyEvent *>(event);

		for (KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyDown(keyEvent->key());

		break;

	case QEvent::KeyRelease:
		keyEvent = static_cast<QKeyEvent *>(event);

		for (KeyboardInputDeviceHandler* handler : handlersKeyboard)
			handler->onKeyUp(keyEvent->key());

		break;

		/*
	case QEvent::Shortcut:
		QShortcutEvent *sc = static_cast<QShortcutEvent *>(event);
		const QKeySequence &ks = sc->key();
		return true;
		break;
		*/
	}

	return false;
}

#endif