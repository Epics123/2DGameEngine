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
		MH_CORE_ASSERT(!sInstance, "Application already exists!");
		sInstance = this;

		mWindow = Window::createWindow(WindowProps(name));
		mWindow->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		Renderer::init();

		mImGuiLayer = new ImGuiLayer();
		pushOverlay(mImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::shutdown();
	}

	void Application::run()
	{
		while (mRunning)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - mLastFrameTime;
			mLastFrameTime = time;

			if (!mMinimized)
			{
				{
					for (Layer* layer : mLayerStack)
						layer->onUpdate(timestep);
				}
				mImGuiLayer->begin();

				{
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
		EventDispatcher dispatcher(e);
		dispatcher.dispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClosed));
		dispatcher.dispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(Application::onWindowResize));

		for (auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it)
		{
			if (e.mHandled)
				break;
			(*it)->onEvent(e);
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