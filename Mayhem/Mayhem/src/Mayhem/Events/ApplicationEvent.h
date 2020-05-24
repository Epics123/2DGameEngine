#pragma once

#include "Event.h"
#include <sstream>

namespace Mayhem
{
	class MAYHEM_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:mWidth(width), mHeight(height){}

		inline unsigned int getWidth() const { return mWidth; }
		inline unsigned int getHeight() const { return mHeight; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent:  " << mWidth << ", " << mHeight;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(APPLICATION)

		static EventType getStaticType() { return EventType::WINDOW_RESIZE; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "WindowResize"; }

	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};

	class MAYHEM_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}

		EVENT_CLASS_CATEGORY(APPLICATION)

		static EventType getStaticType() { return EventType::WINDOW_CLOSE; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "WindowClose"; }
	};
}