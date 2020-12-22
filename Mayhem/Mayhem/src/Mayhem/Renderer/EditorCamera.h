#pragma once

#include "Camera.h"
#include "Mayhem/Core/Timestep.h"
#include "Mayhem/Events/Event.h"
#include "Mayhem/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Mayhem
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void onUpdate(Timestep ts);
		void onEvent(Event & e);

		inline float getDistance() const { return mDistance; }
		inline void setDistance(float distance) { mDistance = distance; }

		inline void setViewportSize(float width, float height) { mViewportWidth = width; mViewportHeight = height; updateProjection(); }

		const glm::mat4& getViewMatrix() const { return mViewMatrix; }
		glm::mat4 getViewProjection() const { return mProjection * mViewMatrix; }

		glm::vec3 getUpDirection() const;
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;
		const glm::vec3& getPosition() const { return mPosition; }
		glm::quat getOrientation() const;

		float getPitch() const { return mPitch; }
		float getYaw() const { return mYaw; }
	private:
		void updateProjection();
		void updateView();

		bool onMouseScroll(MouseScrolledEvent & e);

		void mousePan(const glm::vec2 & delta);
		void mouseRotate(const glm::vec2 & delta);
		void mouseZoom(float delta);

		glm::vec3 calculatePosition() const;

		std::pair<float, float> panSpeed() const;
		float rotationSpeed() const;
		float zoomSpeed() const;
	private:
		float mFOV = 45.0f, mAspectRatio = 1.778f, mNearClip = 0.1f, mFarClip = 1000.0f;

		glm::mat4 mViewMatrix;
		glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 mFocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 mInitialMousePosition = { 0.0f, 0.0f };

		float mDistance = 10.0f;
		float mPitch = 0.0f, mYaw = 0.0f;

		float mViewportWidth = 1280, mViewportHeight = 720;
	};
}