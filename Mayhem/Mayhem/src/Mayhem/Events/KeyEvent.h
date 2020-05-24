#pragma once

#include "Event.h"
#include <sstream>

namespace Mayhem
{
	class MAYHEM_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(KEYBOARD | INPUT)

	protected:
		int mKeyCode;

		KeyEvent(int keyCode)
			:mKeyCode(keyCode){}
	};

	class MAYHEM_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), mRepeatCount(repeatCount) { }

		inline int getRepeatCount() const { return mRepeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
			return ss.str();
		}

		static EventType getStaticType() { return EventType::KEY_PRESSED; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "KeyPressed"; }
		
	private:
		int mRepeatCount;
	};

	class MAYHEM_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::KEY_RELEASED; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "KeyReleased"; }
	};
}