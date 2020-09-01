#pragma once

#include <glm/glm.hpp>

namespace Mayhem
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection)
			:mProjection(projection) {}

		const glm::mat4& getProjection() const { return mProjection; }

	private:
		glm::mat4 mProjection;
	};
}