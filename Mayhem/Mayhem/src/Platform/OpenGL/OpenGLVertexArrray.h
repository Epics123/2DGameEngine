#pragma once

#include "Mayhem/Renderer/VertexArray.h"

namespace Mayhem
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return mVertexBuffers; }
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override { return mIndexBuffer; }

	private:
		uint32_t mRendererID;
		std::vector<Ref<VertexBuffer>> mVertexBuffers;
		Ref<IndexBuffer> mIndexBuffer;
	};
}