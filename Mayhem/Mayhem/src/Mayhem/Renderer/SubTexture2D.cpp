#include "mpch.h"
#include "SubTexture2D.h"

namespace Mayhem
{

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:mTexture(texture)
	{
		mTexCoords[0] = { min.x, min.y };
		mTexCoords[1] = { max.x, min.y };
		mTexCoords[2] = { max.x, max.y };
		mTexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->getWidth(), (coords.y * cellSize.y) / texture->getHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}
}