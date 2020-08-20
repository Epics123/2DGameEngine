#pragma once

#include "Event.h"
#include "Mayhem/Core/Input.h"

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

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

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

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseScroll"; }

	private:
		float mXOffset;
		float mYOffset;
	};

	class MAYHEM_API MouseButtonEvent : public Event
	{
	public:
		inline MouseCode getMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(MouseCode button)
			:mButton(button){ }

		MouseCode mButton;
	};

	class MAYHEM_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			:MouseButtonEvent(button){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:  " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseButtonPressed"; }
	};

	class MAYHEM_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			:MouseButtonEvent(button){}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:  " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

		virtual EventType getEventType() const override { return getStaticType(); }
		virtual const char* getName() const override { return "MouseButtonReleased"; }
	};
}