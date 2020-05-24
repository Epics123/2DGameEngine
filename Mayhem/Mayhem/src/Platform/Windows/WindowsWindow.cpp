#include "mpch.h"
#include "WindowsWindow.h"

namespace Mayhem
{
	static bool sGLFWInitialized = false;

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

			sGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);
		glfwSetWindowUserPointer(mWindow, &mData);
		setVsync(true);
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
