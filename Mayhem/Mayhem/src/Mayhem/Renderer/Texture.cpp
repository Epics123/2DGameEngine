#include "mpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mayhem
{

	Ref<Mayhem::Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}