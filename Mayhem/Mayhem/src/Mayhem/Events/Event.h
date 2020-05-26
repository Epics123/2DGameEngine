#pragma once

#include "Mayhem/Core.h"

namespace Mayhem
{
	enum class EventType
	{
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVE, MOUSE_SCROLL
	};

	enum EventCategory
	{
		None = 0,
		APPLICATION   = 1 << 0,
		INPUT         = 1 << 1,
		KEYBOARD      = 1 << 2,
		MOUSE	      = 1 << 3,
		MOUSE_BUTTON  = 1 << 4
	};

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class MAYHEM_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}
		
		bool mHandled = false;

	protected:
	};

	class MAYHEM_API EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			:mEvent(event){}

		template <typename T>
		bool dispatchEvent(EventFn<T> func)
		{
			if (mEvent.getEventType() == T::getStaticType())
			{
				mEvent.mHandled = func(*(T*)& mEvent);
				return true;
			}
			return false;
		}

	private:
		Event& mEvent;
	};

	inline std::ostream& operator<< (std::ostream& output, const Event& e)
	{
		return output << e.toString();
	}
}
