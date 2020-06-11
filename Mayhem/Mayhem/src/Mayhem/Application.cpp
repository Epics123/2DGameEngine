#include "mpch.h"
#include "Application.h"

#include "Mayhem/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Mayhem
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sInstance = nullptr;

	Application::Application()
	{
		MH_CORE_ASSERT(!sInstance, "Application already exists!");
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::createWindow());
		mWindow->setEventCallback(BIND_EVENT_FN(onEvent));

		mImGuiLayer = new ImGuiLayer();
		pushOverlay(mImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (mRunning)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - mLastFrameTime;
			mLastFrameTime = time;

			for (Layer* layer : mLayerStack)
				layer->onUpdate(timestep);

			mImGuiLayer->begin();
			for (Layer* layer : mLayerStack)
				layer->onImGuiRender();
			mImGuiLayer->end();

			mWindow->onUpdate();
		}
	}

	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.mHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		mLayerStack.pushLayer(layer);
		layer->onAttatch();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		mLayerStack.pushLayer(overlay);
		overlay->onAttatch();
	}

	bool Application::onWindowClosed(WindowCloseEvent& event)
	{
		mRunning = false;
		return true;
	}
}