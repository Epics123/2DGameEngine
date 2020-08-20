#pragma once

#include "Mayhem/Core/Core.h"

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
		APPLICATION   = BIT(0),
		INPUT         = BIT(1),
		KEYBOARD      = BIT(2),
		MOUSE	      = BIT(3),
		MOUSE_BUTTON  = BIT(4)
	};

#define EVENT_CLASS_CATEGORY(category, ...) virtual int getCategoryFlags() const override { return category; }

	class MAYHEM_API Event
	{
	public:
		virtual ~Event() = default;

		bool mHandled = false;
		
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}	

	protected:
	};

	class MAYHEM_API EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:mEvent(event){}

		template <typename T, typename F>
		bool dispatchEvent(const F& func)
		{
			if (mEvent.getEventType() == T::getStaticType())
			{
				mEvent.mHandled = func(static_cast<T&>(mEvent));
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
