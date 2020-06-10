#include "mpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArrray.h"

namespace Mayhem
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}