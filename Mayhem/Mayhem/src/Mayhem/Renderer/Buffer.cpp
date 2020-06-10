#include "mpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mayhem
{
	VertexBuffer* VertexBuffer::create(float* verticies, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(verticies, size);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indicies, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indicies, count);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}