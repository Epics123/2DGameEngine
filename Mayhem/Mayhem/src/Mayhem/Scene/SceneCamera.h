#pragma once

#include "Mayhem/Renderer/Camera.h"

namespace Mayhem
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void setOrthographic(float size, float nearClip, float farClip);
		void setPerspective(float verticalFOV, float nearClip, float farClip);

		void setViewportSize(uint32_t width, uint32_t height);

		float getPerspectiveVerticalFOV() const { return mPerspectiveFOV; }
		void setPerspectiveVerticalFOV(float verticalFov) { mPerspectiveFOV = verticalFov; recalculateProjection(); }
		float getPerspectiveNearClip() const { return mPerspectiveNear; }
		void setPerspectiveNearClip(float nearClip) { mPerspectiveNear = nearClip; recalculateProjection(); }
		float getPerspectiveFarClip() const { return mPerspectiveFar; }
		void setPerspectiveFarClip(float farClip) { mPerspectiveFar = farClip; recalculateProjection(); }


		float getOrthographicSize() const { return mOrthographicSize; }
		void setOrthographicSize(float size) { mOrthographicSize = size; recalculateProjection(); }
		float getOrthographicNearClip() const { return mOrthographicNear; }
		void setOrthographicNearClip(float nearClip) { mOrthographicNear = nearClip; recalculateProjection(); }
		float getOrthographicFarClip() const { return mOrthographicFar; }
		void setOrthographicFarClip(float farClip) { mOrthographicFar = farClip; recalculateProjection(); }

		ProjectionType getProjectionType() const { return mProjectionType; }
		void setProjectionType(ProjectionType type) { mProjectionType = type; recalculateProjection(); }

	private:
		void recalculateProjection();

	private:
		ProjectionType mProjectionType = ProjectionType::Orthographic;

		float mOrthographicSize = 10.0f;
		float mOrthographicNear = -1.0f, mOrthographicFar = 1.0f;

		float mPerspectiveFOV = glm::radians(45.0f);
		float mPerspectiveNear = 0.01f, mPerspectiveFar = 1000.0f;

		float mAspectRatio = 0.0f;
	};
}