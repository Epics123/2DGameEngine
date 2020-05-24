#pragma once

#include "Event.h"

namespace Mayhem
{
	class MAYHEM_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			:mMouseX(x), mMouseY(y){}

		inline float getX() const { return mMouseX; }
		inline float getY() const { return mMouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent:  (" << mMouseX << ", " << mMouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(MOUSE, INPUT)

		static EventType getStaticType() { return EventType::MOUSE_MOVE; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseMove"; }

	private:
		float mMouseX;
		float mMouseY;
	};

	class MAYHEM_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:mXOffset(xOffset), mYOffset(yOffset){ }

		inline float getXOffset() const { return mXOffset; }
		inline float getYOffset() const { return mYOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent:  (" << mXOffset << ", " << mYOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(MOUSE, INPUT)

		static EventType getStaticType() { return EventType::MOUSE_SCROLL; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseScroll"; }

	private:
		float mXOffset;
		float mYOffset;
	};

	class MAYHEM_API MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(MOUSE | INPUT)

	protected:
		MouseButtonEvent(int button)
			:mButton(button){ }

		int mButton;
	};

	class MAYHEM_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:  " << mButton;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MOUSE_BUTTON_PRESSED; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseButtonPressed"; }
	};

	class MAYHEM_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:  " << mButton;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MOUSE_BUTTON_RELEASED; }
		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseButtonReleased"; }
	};
}