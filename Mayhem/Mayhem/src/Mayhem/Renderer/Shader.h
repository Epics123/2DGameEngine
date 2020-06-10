#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Mayhem
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;

		static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}