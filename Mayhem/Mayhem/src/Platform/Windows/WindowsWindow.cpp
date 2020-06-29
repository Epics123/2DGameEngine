#include "mpch.h"
#include "WindowsWindow.h"

#include "Mayhem/Events/ApplicationEvent.h"
#include "Mayhem/Events/KeyEvent.h"
#include "Mayhem/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Mayhem
{
	static uint8_t sGLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		MH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Mayhem::WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		MH_PROFILE_FUNCTION();
		init(props);
	}

	Mayhem::WindowsWindow::~WindowsWindow()
	{
		MH_PROFILE_FUNCTION();

		shutdown();
	}

	void WindowsWindow::onUpdate()
	{
		MH_PROFILE_FUNCTION();

		glfwPollEvents();
		mContext->swapBuffers();
	}

	void WindowsWindow::setVsync(bool enabled)
	{
		MH_PROFILE_FUNCTION();

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
		MH_PROFILE_FUNCTION();
		mData.Title = props.Title;
		mData.Width = props.Width;
		mData.Height = props.Height;

		MH_CORE_INFO("CreatingWindow {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (sGLFWWindowCount == 0)
		{
			MH_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			MH_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			MH_PROFILE_SCOPE("glfwCreateWindow");
			mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
			++sGLFWWindowCount;
		}
		
		mContext = new OpenGLContext(mWindow);
		mContext->init();

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
		MH_PROFILE_FUNCTION();

		glfwDestroyWindow(mWindow);
		--sGLFWWindowCount;

		if (sGLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	Window* Window::createWindow(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
}
