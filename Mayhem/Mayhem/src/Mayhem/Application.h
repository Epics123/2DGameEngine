#pragma once

#include "Core.h"

namespace Mayhem
{
	class MAYHEM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	//To be defined in client
	Application* createApplication();
}

