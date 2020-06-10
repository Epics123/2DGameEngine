#pragma once

#include "Mayhem/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Mayhem
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

	private:
		uint32_t mRendererID;
	};
}