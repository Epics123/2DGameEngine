#include "mpch.h"
#include"Shader.h"

#include "Mayhem/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Mayhem
{
	Ref<Shader> Shader::create(const std::string& filepath)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:
			MH_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		MH_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		MH_CORE_ASSERT(!exists(name), "Shader already exists!");
		mShaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		MH_CORE_ASSERT(mShaders.find(name) == mShaders.end(), "Shader already exists!");
		add(name, shader);
	}


	Ref<Mayhem::Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Ref<Mayhem::Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Ref<Mayhem::Shader> ShaderLibrary::get(const std::string& name)
	{
		MH_CORE_ASSERT(exists(name), "Shader not found!");
		return mShaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return mShaders.find(name) != mShaders.end();
	}
}