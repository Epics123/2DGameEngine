#include "mpch.h"
#include"Shader.h"

#include "Mayhem/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Mayhem
{
	Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}