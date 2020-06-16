#pragma once

#include <glm/glm.hpp>

namespace Mayhem
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void setProjection(float left, float right, float bottom, float top);
		
		float getRotation() const { return mRotation; }

		const glm::vec3& getPostition() const { return mPosition; }
		const glm::mat4& getProjMatrix() const { return mProjMatrix; }
		const glm::mat4& getViewMatrix() const { return mViewMatrix; }
		const glm::mat4& getViewProjMatrix() const { return mViewProjMatrix; }

		void setPostition(const glm::vec3& position) { mPosition = position; recalculateViewMatrix(); }
		void setRotation(float rotation) { mRotation = rotation; recalculateViewMatrix(); }


	private:
		void recalculateViewMatrix();

	private:
		glm::mat4 mProjMatrix;
		glm::mat4 mViewMatrix;
		glm::mat4 mViewProjMatrix;

		glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
		float mRotation = 0.0f;
	};
}