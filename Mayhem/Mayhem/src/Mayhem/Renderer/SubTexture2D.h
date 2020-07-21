#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Mayhem
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D>getTexture() const { return mTexture; }
		const glm::vec2* getTexCoords() const { return mTexCoords; }

		static Ref<SubTexture2D> createFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize);

	private:
		Ref<Texture2D> mTexture;

		glm::vec2 mTexCoords[4];
	};
}