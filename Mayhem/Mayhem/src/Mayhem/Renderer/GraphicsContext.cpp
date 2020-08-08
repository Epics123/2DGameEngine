#include "mpch.h"
#include "Mayhem/Renderer/GraphicsContext.h"

#include "Mayhem/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Mayhem
{
	Scope<GraphicsContext> GraphicsContext::create(void* window)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		MH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}