#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Mayhem/ImGui/ImGuiLayer.h"

#include "Mayhem/Renderer/Shader.h"
#include "Mayhem/Renderer/Buffer.h"
#include "Mayhem/Renderer/VertexArray.h"

#include "Mayhem/Renderer/OrthographicCamera.h"

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

		inline Window& getWindow() { return *mWindow; }

		inline static Application& getInstance() { return *sInstance; }

	private:
		std::unique_ptr<Window> mWindow;
		ImGuiLayer* mImGuiLayer;
		bool mRunning = true;
		LayerStack mLayerStack;

		std::shared_ptr<Shader> mShader;
		std::shared_ptr<VertexArray> mVertexArray;

		std::shared_ptr<VertexArray> mSquareVA;
		std::shared_ptr<Shader> mBlueShader;

		OrthographicCamera mCamera;

		bool onWindowClosed(WindowCloseEvent& event);

	private:
		static Application* sInstance;
	};

	//To be defined in client
	Application* createApplication();
}

