#pragma once

#include "Mayhem/Core/Core.h"

namespace Mayhem
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication   = BIT(0),
		EventCategoryInput         = BIT(1),
		EventCategoryKeyboard      = BIT(2),
		EventCategoryMouse 	       = BIT(3),
		EventCategoryMouseButton   = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

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
