#include "mpch.h"
#include "Mayhem/Core/Window.h"

#ifdef MH_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Mayhem
{
	Scope<Window> Window::createWindow(const WindowProps& props)
	{
		#ifdef MH_PLATFORM_WINDOWS
				return CreateScope<WindowsWindow>(props);
		#else
				MH_CORE_ASSERT(false, "Unknown Platform!");
				return nullptr;
		#endif // MH_PLATFORM_WINDOWS
	}
}