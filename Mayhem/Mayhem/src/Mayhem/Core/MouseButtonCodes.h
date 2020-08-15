#pragma once

namespace Mayhem
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

//from glfw3.h
#define MH_MOUSE_BUTTON_0         ::Mayhem::Mouse::Button0
#define MH_MOUSE_BUTTON_1         ::Mayhem::Mouse::Button1
#define MH_MOUSE_BUTTON_2         ::Mayhem::Mouse::Button2
#define MH_MOUSE_BUTTON_3         ::Mayhem::Mouse::Button3
#define MH_MOUSE_BUTTON_4         ::Mayhem::Mouse::Button4
#define MH_MOUSE_BUTTON_5         ::Mayhem::Mouse::Button5
#define MH_MOUSE_BUTTON_6         ::Mayhem::Mouse::Button6
#define MH_MOUSE_BUTTON_7         ::Mayhem::Mouse::Button7
#define MH_MOUSE_BUTTON_LAST      ::Mayhem::Mouse::ButtonLast
#define MH_MOUSE_BUTTON_LEFT      ::Mayhem::Mouse::ButtonLeft
#define MH_MOUSE_BUTTON_RIGHT     ::Mayhem::Mouse::ButtonRight
#define MH_MOUSE_BUTTON_MIDDLE    ::Mayhem::Mouse::ButtonMiddle