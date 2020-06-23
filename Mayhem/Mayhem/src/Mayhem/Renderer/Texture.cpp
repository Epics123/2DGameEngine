#include "mpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mayhem
{

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Mayhem::Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}