#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
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

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
		LayerStack mLayerStack;

		bool onWindowClosed(WindowCloseEvent& event);
	};

	//To be defined in client
	Application* createApplication();
}

