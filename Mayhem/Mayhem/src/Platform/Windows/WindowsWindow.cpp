#include "mpch.h"
#include "WindowsWindow.h"

#include "Mayhem/Events/ApplicationEvent.h"
#include "Mayhem/Events/KeyEvent.h"
#include "Mayhem/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Mayhem
{
	static bool sGLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		MH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Mayhem::WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	Mayhem::WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}

	void WindowsWindow::setVsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mData.vSync = enabled;
	}

	bool WindowsWindow::isVsync() const
	{
		return mData.vSync;
	}

	void Mayhem::WindowsWindow::init(const WindowProps& props)
	{
		mData.Title = props.Title;
		mData.Width = props.Width;
		mData.Height = props.Height;

		MH_CORE_INFO("CreatingWindow {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!sGLFWInitialized)
		{
			//TODO: glfw terminate on system shutdown
			int success = glfwInit();
			MH_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			sGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MH_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(mWindow, &mData);
		setVsync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				
				WindowResizeEvent event(width, height);
				data.EventCallback(event);			
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMoveEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void Mayhem::WindowsWindow::shutdown()
	{
		glfwDestroyWindow(mWindow);
	}

	Window* Window::createWindow(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
}
