#pragma once

#include "Mayhem/Renderer/Buffer.h"

namespace Mayhem
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual const BufferLayout& getLayout() const override { return mLayout; }
		virtual void setLayout(const BufferLayout& layout) override { mLayout = layout; }

	private:
		uint32_t mRendererID;
		BufferLayout mLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual uint32_t getCount() const { return mCount; }

	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};
}