#pragma once

//from glfw3.h

namespace Mayhem
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
#define MH_KEY_SPACE              ::Mayhem::Key::Space
#define MH_KEY_APOSTROPHE         ::Mayhem::Key::Apostrophe  /* ' */
#define MH_KEY_COMMA              ::Mayhem::Key::Comma  /* , */
#define MH_KEY_MINUS              ::Mayhem::Key::Minus  /* - */
#define MH_KEY_PERIOD             ::Mayhem::Key::Period  /* . */
#define MH_KEY_SLASH              ::Mayhem::Key::Slash  /* / */
#define MH_KEY_0                  ::Mayhem::Key::D0
#define MH_KEY_1                  ::Mayhem::Key::D1
#define MH_KEY_2                  ::Mayhem::Key::D2
#define MH_KEY_3                  ::Mayhem::Key::D3
#define MH_KEY_4                  ::Mayhem::Key::D4
#define MH_KEY_5                  ::Mayhem::Key::D5
#define MH_KEY_6                  ::Mayhem::Key::D6
#define MH_KEY_7                  ::Mayhem::Key::D7
#define MH_KEY_8                  ::Mayhem::Key::D8
#define MH_KEY_9                  ::Mayhem::Key::D9
#define MH_KEY_SEMICOLON          ::Mayhem::Key::Semicolon  /* ; */
#define MH_KEY_EQUAL              ::Mayhem::Key::Equal  /* = */
#define MH_KEY_A                  ::Mayhem::Key::A
#define MH_KEY_B                  ::Mayhem::Key::B
#define MH_KEY_C                  ::Mayhem::Key::C
#define MH_KEY_D                  ::Mayhem::Key::D
#define MH_KEY_E                  ::Mayhem::Key::E
#define MH_KEY_F                  ::Mayhem::Key::F
#define MH_KEY_G                  ::Mayhem::Key::G
#define MH_KEY_H                  ::Mayhem::Key::H
#define MH_KEY_I                  ::Mayhem::Key::I
#define MH_KEY_J                  ::Mayhem::Key::J
#define MH_KEY_K                  ::Mayhem::Key::K
#define MH_KEY_L                  ::Mayhem::Key::L
#define MH_KEY_M                  ::Mayhem::Key::M
#define MH_KEY_N                  ::Mayhem::Key::N
#define MH_KEY_O                  ::Mayhem::Key::O
#define MH_KEY_P                  ::Mayhem::Key::P
#define MH_KEY_Q                  ::Mayhem::Key::Q
#define MH_KEY_R                  ::Mayhem::Key::R
#define MH_KEY_S                  ::Mayhem::Key::S
#define MH_KEY_T                  ::Mayhem::Key::T
#define MH_KEY_U                  ::Mayhem::Key::U
#define MH_KEY_V                  ::Mayhem::Key::V
#define MH_KEY_W                  ::Mayhem::Key::W
#define MH_KEY_X                  ::Mayhem::Key::X
#define MH_KEY_Y                  ::Mayhem::Key::Y
#define MH_KEY_Z                  ::Mayhem::Key::Z
#define MH_KEY_LEFT_BRACKET       ::Mayhem::Key::LeftBracket  /* [ */
#define MH_KEY_BACKSLASH          ::Mayhem::Key::Backslash  /* \ */
#define MH_KEY_RIGHT_BRACKET      ::Mayhem::Key::RightBracket  /* ] */
#define MH_KEY_GRAVE_ACCENT       ::Mayhem::Key::GraveAccent  /* ` */
#define MH_KEY_WORLD_1            ::Mayhem::Key::World1 /* non-US #1 */
#define MH_KEY_WORLD_2            ::Mayhem::Key::World2 /* non-US #2 */

/* Function keys */
#define MH_KEY_ESCAPE             ::Mayhem::Key::Escape	
#define MH_KEY_ENTER              ::Mayhem::Key::Enter
#define MH_KEY_TAB                ::Mayhem::Key::Tab
#define MH_KEY_BACKSPACE          ::Mayhem::Key::Backspace
#define MH_KEY_INSERT             ::Mayhem::Key::Insert
#define MH_KEY_DELETE             ::Mayhem::Key::Delete
#define MH_KEY_RIGHT              ::Mayhem::Key::Right
#define MH_KEY_LEFT               ::Mayhem::Key::Left
#define MH_KEY_DOWN               ::Mayhem::Key::Down
#define MH_KEY_UP                 ::Mayhem::Key::Up
#define MH_KEY_PAGE_UP            ::Mayhem::Key::PageUp
#define MH_KEY_PAGE_DOWN          ::Mayhem::Key::PageDown
#define MH_KEY_HOME               ::Mayhem::Key::Home
#define MH_KEY_END                ::Mayhem::Key::End
#define MH_KEY_CAPS_LOCK          ::Mayhem::Key::CapsLock
#define MH_KEY_SCROLL_LOCK        ::Mayhem::Key::ScrollLock
#define MH_KEY_NUM_LOCK           ::Mayhem::Key::NumLock
#define MH_KEY_PRINT_SCREEN       ::Mayhem::Key::PrintScreen
#define MH_KEY_PAUSE              ::Mayhem::Key::Pause
#define MH_KEY_F1                 ::Mayhem::Key::F1
#define MH_KEY_F2                 ::Mayhem::Key::F2
#define MH_KEY_F3                 ::Mayhem::Key::F3
#define MH_KEY_F4                 ::Mayhem::Key::F4
#define MH_KEY_F5                 ::Mayhem::Key::F5
#define MH_KEY_F6                 ::Mayhem::Key::F6
#define MH_KEY_F7                 ::Mayhem::Key::F7
#define MH_KEY_F8                 ::Mayhem::Key::F8
#define MH_KEY_F9                 ::Mayhem::Key::F9
#define MH_KEY_F10                ::Mayhem::Key::F10
#define MH_KEY_F11                ::Mayhem::Key::F11
#define MH_KEY_F12                ::Mayhem::Key::F12
#define MH_KEY_F13                ::Mayhem::Key::F13
#define MH_KEY_F14                ::Mayhem::Key::F14
#define MH_KEY_F15                ::Mayhem::Key::F15
#define MH_KEY_F16                ::Mayhem::Key::F16
#define MH_KEY_F17                ::Mayhem::Key::F17
#define MH_KEY_F18                ::Mayhem::Key::F18
#define MH_KEY_F19                ::Mayhem::Key::F19
#define MH_KEY_F20                ::Mayhem::Key::F20
#define MH_KEY_F21                ::Mayhem::Key::F21
#define MH_KEY_F22                ::Mayhem::Key::F22
#define MH_KEY_F23                ::Mayhem::Key::F23
#define MH_KEY_F24                ::Mayhem::Key::F24
#define MH_KEY_F25                ::Mayhem::Key::F25
#define MH_KEY_KP_0               ::Mayhem::Key::KP0
#define MH_KEY_KP_1               ::Mayhem::Key::KP1
#define MH_KEY_KP_2               ::Mayhem::Key::KP2
#define MH_KEY_KP_3               ::Mayhem::Key::KP3
#define MH_KEY_KP_4               ::Mayhem::Key::KP4
#define MH_KEY_KP_5               ::Mayhem::Key::KP5
#define MH_KEY_KP_6               ::Mayhem::Key::KP6
#define MH_KEY_KP_7               ::Mayhem::Key::KP7
#define MH_KEY_KP_8               ::Mayhem::Key::KP8
#define MH_KEY_KP_9               ::Mayhem::Key::KP9
#define MH_KEY_KP_DECIMAL         ::Mayhem::Key::KPDecimal
#define MH_KEY_KP_DIVIDE          ::Mayhem::Key::KPDivide
#define MH_KEY_KP_MULTIPLY        ::Mayhem::Key::KPMultiply
#define MH_KEY_KP_SUBTRACT        ::Mayhem::Key::KPSubtract
#define MH_KEY_KP_ADD             ::Mayhem::Key::KPAdd
#define MH_KEY_KP_ENTER           ::Mayhem::Key::KPEnter
#define MH_KEY_KP_EQUAL           ::Mayhem::Key::KPEqual
#define MH_KEY_LEFT_SHIFT         ::Mayhem::Key::LeftShift
#define MH_KEY_LEFT_CONTROL       ::Mayhem::Key::LeftControl
#define MH_KEY_LEFT_ALT           ::Mayhem::Key::LeftAlt
#define MH_KEY_LEFT_SUPER         ::Mayhem::Key::LeftSuper
#define MH_KEY_RIGHT_SHIFT        ::Mayhem::Key::RightShift
#define MH_KEY_RIGHT_CONTROL      ::Mayhem::Key::RightControl
#define MH_KEY_RIGHT_ALT          ::Mayhem::Key::RightAlt
#define MH_KEY_RIGHT_SUPER        ::Mayhem::Key::RightSuper
#define MH_KEY_MENU               ::Mayhem::Key::Menu

#define MH_KEY_LAST               MH_KEY_MENU