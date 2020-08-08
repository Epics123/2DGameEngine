#pragma once

#include "Mayhem/Core/Core.h"

namespace Mayhem
{
	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t getColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpec& getSpecification() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpec& spec);
	};
}