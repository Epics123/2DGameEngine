#pragma once

#include "Mayhem/Renderer/RendererAPI.h"

namespace Mayhem
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void init() override;
		virtual  void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
	};
}