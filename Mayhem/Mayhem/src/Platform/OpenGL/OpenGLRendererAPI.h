#pragma once

#include "Mayhem/Renderer/RendererAPI.h"

namespace Mayhem
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}