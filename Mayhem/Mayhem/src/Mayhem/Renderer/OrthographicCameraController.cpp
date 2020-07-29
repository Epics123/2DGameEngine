#include "mpch.h"
#include "Mayhem/Renderer/OrthographicCameraController.h"

#include "Mayhem/Core/Input.h"
#include "Mayhem/Core/KeyCodes.h"

namespace Mayhem
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:mAspectRatio(aspectRatio), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel), mRotation(rotation)
	{

	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		MH_PROFILE_FUNCTION();

		if (Input::isKeyPressed(MH_KEY_A))
			mCameraPosition.x -= mCameraTranslationSpeed * ts;
		else if (Input::isKeyPressed(MH_KEY_D))
			mCameraPosition.x += mCameraTranslationSpeed * ts;

		if (Input::isKeyPressed(MH_KEY_S))
			mCameraPosition.y -= mCameraTranslationSpeed * ts;
		else if (Input::isKeyPressed(MH_KEY_W))
			mCameraPosition.y += mCameraTranslationSpeed * ts;

		if (mRotation)
		{
			if (Input::isKeyPressed(MH_KEY_Q))
				mCameraRotation += mCameraRotationSpeed * ts;
			else if (Input::isKeyPressed(MH_KEY_E))
				mCameraRotation -= mCameraRotationSpeed * ts;

			mCamera.setRotation(mCameraRotation);
		}	

		mCamera.setPostition(mCameraPosition);
		
		mCameraTranslationSpeed = mZoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		MH_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatchEvent<MouseScrolledEvent>(MH_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatchEvent<WindowResizeEvent>(MH_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	void OrthographicCameraController::calculateView()
	{
		mCamera.setProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		MH_PROFILE_FUNCTION();

		mZoomLevel -= e.getYOffset() * 0.5f;
		mZoomLevel = std::max(mZoomLevel, 0.25f);
		calculateView();

		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		MH_PROFILE_FUNCTION();

		mAspectRatio = (float)e.getWidth() / (float)e.getHeight();
		calculateView();

		return false;
	}

}