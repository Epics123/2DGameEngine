#pragma once

#include "Event.h"
#include "Mayhem/Core/Input.h"

namespace Mayhem
{
	class MAYHEM_API KeyEvent : public Event
	{
	public:
		KeyCode getKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(KeyCode keycode)
			:mKeyCode(keycode){}
		
		KeyCode mKeyCode;
	};

	class MAYHEM_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), mRepeatCount(repeatCount) { }

		int getRepeatCount() const { return mRepeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "KeyPressed"; }
		
	private:
		int mRepeatCount;
	};

	class MAYHEM_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			:KeyEvent(keycode){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "KeyReleased"; }
	};

	class MAYHEM_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode)
		{
		}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "KeyTyped"; }
	};
}