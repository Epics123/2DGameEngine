#include "mpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mayhem
{

	SceneCamera::SceneCamera()
	{
		recalculateProjection();
	}

	void SceneCamera::setOrthographic(float size, float nearClip, float farClip)
	{
		mOrthographicSize = size;
		mOrthographicNear = nearClip;
		mOrthographicFar = farClip;

		recalculateProjection();
	}

	void SceneCamera::setViewportSize(uint32_t width, uint32_t height)
	{
		mAspectRatio = (float)width / (float)height;
		recalculateProjection();
	}

	void SceneCamera::recalculateProjection()
	{
		float orthoLeft = -mOrthographicSize * mAspectRatio * 0.5f;
		float orthoRight = mOrthographicSize * mAspectRatio * 0.5f;
		float orthoBottom = -mOrthographicSize * 0.5f;
		float orthoTop = mOrthographicSize * 0.5f;

		mProjection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, mOrthographicNear, mOrthographicFar);
	}

}