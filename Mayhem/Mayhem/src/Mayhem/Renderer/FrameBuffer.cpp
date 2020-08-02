#include "mpch.h"
#include "FrameBuffer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Mayhem/Renderer/Renderer.h"

namespace Mayhem
{

	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpec& spec)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(spec);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}