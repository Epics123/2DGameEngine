#include "mpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Mayhem
{
	Application::Application()
	{
		mWindow = std::unique_ptr<Window>(Window::createWindow());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (mRunning)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			mWindow->onUpdate();
		}
	}
}