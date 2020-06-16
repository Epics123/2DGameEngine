#pragma once

#include "Mayhem/Renderer/OrthographicCamera.h"
#include "Mayhem/Core/Timestep.h"

#include "Mayhem/Events/ApplicationEvent.h"
#include "Mayhem/Events/MouseEvent.h"

namespace Mayhem
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return mCamera; }
		const OrthographicCamera& getCamera() const { return mCamera; }

	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);

	private:
		float mAspectRatio;
		float mZoomLevel = 1.0f;
		OrthographicCamera mCamera;

		bool mRotation;
		glm::vec3 mCameraPosition = { 0.0f, 0.0f, 0.0f };
		float mCameraRotation = 0.0f;
		float mCameraTranslationSpeed = 2.0f;
		float mCameraRotationSpeed = 45.0f;
	};
}