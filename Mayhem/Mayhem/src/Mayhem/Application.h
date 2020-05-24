#pragma once

#include "Core.h"
#include "Window.h"

namespace Mayhem
{
	class MAYHEM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
	};

	//To be defined in client
	Application* createApplication();
}

