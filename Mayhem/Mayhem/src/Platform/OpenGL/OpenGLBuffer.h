#pragma once

#include "Mayhem/Renderer/Buffer.h"

namespace Mayhem
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const;
		virtual void unBind() const;

	private:
		uint32_t mRendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unBind() const;

		virtual uint32_t getCount() const { return mCount; }

	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};
}