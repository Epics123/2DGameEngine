#pragma once

#include "Mayhem/Renderer/Camera.h"

namespace Mayhem
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void setOrthographic(float size, float nearClip, float farClip);
		void setViewportSize(uint32_t width, uint32_t height);

		float getOrthographicSize() const { return mOrthographicSize; }
		void setOrthographicSize(float size) { mOrthographicSize = size; recalculateProjection(); }

	private:
		void recalculateProjection();

	private:
		float mOrthographicSize = 10.0f;
		float mOrthographicNear = -1.0f, mOrthographicFar = 1.0f;

		float mAspectRatio = 0.0f;
	};
}