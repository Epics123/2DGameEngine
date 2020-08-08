#pragma once

#include "Mayhem/Renderer/FrameBuffer.h"

namespace Mayhem
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();

		void invalidate();

		virtual void bind() override;
		virtual void unbind() override;

		virtual void resize(uint32_t width, uint32_t height) override;

		virtual uint32_t getColorAttachmentRendererID() const override { return mColorAttachment; }

		virtual const FrameBufferSpec& getSpecification() const override { return mSpecification; }
	private:
		uint32_t mRendererID = 0;
		uint32_t mColorAttachment = 0, mDepthAttachment = 0;
		FrameBufferSpec mSpecification;
	};
}