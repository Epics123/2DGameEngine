#include "mpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mayhem
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: mWindowHandle(windowHandle)
	{
		MH_CORE_ASSERT(mWindowHandle, "Window handle is null!");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MH_CORE_ASSERT(status, "Failed to initialize Glad!");

		MH_CORE_INFO("OpenGL Info: ");
		MH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		MH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		MH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}
}