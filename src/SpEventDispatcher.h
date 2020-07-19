#ifndef SP_EVENT_DISPATCHER_HEADER
#define SP_EVENT_DISPATCHER_HEADER

#include <queue>
#include "SpectrumFoundation.h"
#include "SpEvent.h"
#include "SpVector.h"
#include "SpWindowEventListener.h"
#include "SpKeyboardEventListener.h"
#include "SpMouseEventListener.h"
#include "SpJoypadEventListener.h"
#include "SpCollisionEventListener.h"
#include "SpQueue.h"

namespace NAMESPACE_FOUNDATION
{
	class SpEventDispatcher
	{
	private:
		SpQueue<SpEvent*> events;

		SpVector<SpWindowEventListener*> windowListeners;
		SpVector<SpKeyboardEventListener*> keyboardListeners;
		SpVector<SpMouseEventListener*> mouseListeners;
		SpVector<SpJoypadEventListener*> joypadListeners;
		SpVector<SpCollisionEventListener*> collisionListeners;

		inline SpEvent* pop()
		{
			sp_assert(events.length() > ZERO_SIZE, "StackEmptyException");

			SpEvent* evt = events.front();
			events.pop();

			return evt;
		}

	public:

		API_INTERFACE inline static SpEventDispatcher* instance()
		{
			static SpEventDispatcher* _instance = sp_mem_new(SpEventDispatcher)();
			return _instance;
		}

		API_INTERFACE inline void addWindowListener(SpWindowEventListener* listener)
		{
			windowListeners.add(listener);
		}

		API_INTERFACE inline void addMouseListener(SpMouseEventListener* listener)
		{
			mouseListeners.add(listener);
		}

		API_INTERFACE inline void addKeyboardListener(SpKeyboardEventListener* listener)
		{
			keyboardListeners.add(listener);
		}

		API_INTERFACE inline void addJoypadListener(SpJoypadEventListener* listener)
		{
			joypadListeners.add(listener);
		}

		API_INTERFACE inline void addCollisionListener(SpCollisionEventListener* listener)
		{
			collisionListeners.add(listener);
		}
		
		API_INTERFACE inline void push(SpEvent* evt)
		{
			events.push(evt);
		}

		API_INTERFACE inline sp_bool isEmpty() const
		{
			return events.length() == ZERO_SIZE;
		}

		API_INTERFACE inline void processEvent(SpEvent* evt)
		{
			switch (evt->category())
			{
			case SpEventCategory::Joypad:
				for (SpVectorItem<SpJoypadEventListener*>* item = joypadListeners.last(); item != NULL; item = item->previous())
					item->value()->onJoypadEvent((SpJoypadEvent*)evt);
				//sp_mem_delete((SpJoypadEvent*)evt, SpJoypadEvent);
				break;

			case SpEventCategory::Mouse:
				for (SpVectorItem<SpMouseEventListener*>* item = mouseListeners.last(); item != NULL; item = item->previous())
					item->value()->onMouseEvent((SpMouseEvent*)evt);
				//sp_mem_delete((SpMouseEvent*)evt, SpMouseEvent);
				break;

			case SpEventCategory::Keyboard:
				for (SpVectorItem<SpKeyboardEventListener*>* item = keyboardListeners.last(); item != NULL; item = item->previous())
					item->value()->onKeyboardEvent((SpKeyboardEvent*)evt);
				//sp_mem_delete((SpKeyboardEvent*)evt, SpKeyboardEvent);
				break;

			case SpEventCategory::Collision:
				for (SpVectorItem<SpCollisionEventListener*>* item = collisionListeners.last(); item != NULL; item = item->previous())
					item->value()->onCollisionEvent((SpCollisionEvent*)evt);
				//sp_mem_delete((SpCollisionEvent*)evt, SpCollisionEvent);
				break;

			case SpEventCategory::Gameplay:
				break;

			case SpEventCategory::Window:
				for (SpVectorItem<SpWindowEventListener*>* item = windowListeners.last(); item != NULL; item = item->previous())
					item->value()->onWindowEvent((SpWindowEvent*)evt);
				//sp_mem_delete((SpWindowEvent*)evt, SpWindowEvent);
				break;

			default:
				break;
			}
		}

		API_INTERFACE inline void processAllEvents()
		{
			while (!events.isEmpty())
			{
				SpEvent* evt = events.pop();
				processEvent(evt);
			}
		}

	};
}

#endif // SP_EVENT_DISPATCHER_HEADER