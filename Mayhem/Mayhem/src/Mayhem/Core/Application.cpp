#include "mpch.h"
#include "Application.h"

#include "Mayhem/Renderer/Renderer.h"

#include "Mayhem/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Mayhem
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sInstance = nullptr;

	Application::Application(const std::string& name)
	{
		MH_PROFILE_FUNCTION();

		MH_CORE_ASSERT(!sInstance, "Application already exists!");
		sInstance = this;

		mWindow = Window::createWindow(WindowProps(name));
		mWindow->setEventCallback(BIND_EVENT_FN(onEvent));

		Renderer::init();

		mImGuiLayer = new ImGuiLayer();
		pushOverlay(mImGuiLayer);
	}

	Application::~Application()
	{
		MH_PROFILE_FUNCTION();

		Renderer::shutdown();
	}

	void Application::run()
	{
		MH_PROFILE_FUNCTION();

		while (mRunning)
		{
			MH_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - mLastFrameTime;
			mLastFrameTime = time;

			if (!mMinimized)
			{
				{
					MH_PROFILE_SCOPE("LayerStack onUpdate");
					for (Layer* layer : mLayerStack)
						layer->onUpdate(timestep);
				}
				mImGuiLayer->begin();

				{
					MH_PROFILE_SCOPE("LayerStack onImGuiRender");
					for (Layer* layer : mLayerStack)
						layer->onImGuiRender();
				}
				mImGuiLayer->end();
			}		

			mWindow->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		MH_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));
		dispatcher.dispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.mHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		MH_PROFILE_FUNCTION();

		mLayerStack.pushLayer(layer);
		layer->onAttatch();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		MH_PROFILE_FUNCTION();

		mLayerStack.pushLayer(overlay);
		overlay->onAttatch();
	}

	void Application::close()
	{
		mRunning = false;
	}

	bool Application::onWindowClosed(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e)
	{
		MH_PROFILE_FUNCTION();

		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			mMinimized = true;
			return false;
		}

		mMinimized = false;
		Renderer::onWindowResize(e.getWidth(), e.getHeight());

		return false;
	}
}