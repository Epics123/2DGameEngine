#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Mayhem
{
	class MAYHEM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& event);

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;

		bool onWindowClosed(WindowCloseEvent& event);
	};

	//To be defined in client
	Application* createApplication();
}

