#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Mayhem/Core/Timestep.h"

#include "Mayhem/ImGui/ImGuiLayer.h"

namespace Mayhem
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& event);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline Window& getWindow() { return *mWindow; }

		inline static Application& getInstance() { return *sInstance; }

	private:
		std::unique_ptr<Window> mWindow;
		ImGuiLayer* mImGuiLayer;
		bool mRunning = true;
		LayerStack mLayerStack;
		float mLastFrameTime = 0.0f;

	private:
		bool onWindowClosed(WindowCloseEvent& event);

	private:
		static Application* sInstance;
	};

	//To be defined in client
	Application* createApplication();
}

