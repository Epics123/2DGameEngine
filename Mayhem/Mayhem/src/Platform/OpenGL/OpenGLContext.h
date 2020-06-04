#pragma once

#include "Mayhem/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Mayhem
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* mWindowHandle;
	};
}