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

		virtual uint32_t getColorAttachmentRendererID() const override { return mColorAttachment; }

		virtual const FrameBufferSpec& getSpecification() const override { return mSpecification; }
	private:
		uint32_t mRendererID;
		uint32_t mColorAttachment, mDepthAttachment;
		FrameBufferSpec mSpecification;
	};
}