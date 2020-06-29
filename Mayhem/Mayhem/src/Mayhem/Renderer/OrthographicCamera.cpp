#include "mpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mayhem
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:mProjMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mViewMatrix(1.0f)
	{
		MH_PROFILE_FUNCTION();

		mViewProjMatrix = mProjMatrix * mViewMatrix;
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
	{
		MH_PROFILE_FUNCTION();

		mProjMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		mViewProjMatrix = mProjMatrix * mViewMatrix;
	}

	void OrthographicCamera::recalculateViewMatrix()
	{
		MH_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));

		mViewMatrix = glm::inverse(transform);
		mViewProjMatrix = mProjMatrix * mViewMatrix;
	}
}