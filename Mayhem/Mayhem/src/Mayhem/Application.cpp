#include "mpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Mayhem
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1200, 720);
		MH_TRACE(e);

		while (true);
	}
}