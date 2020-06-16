#include "mpch.h"
#include "Mayhem/OrthographicCameraController.h"

#include "Mayhem/Input.h"
#include "Mayhem/KeyCodes.h"

namespace Mayhem
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:mAspectRatio(aspectRatio), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel), mRotation(rotation)
	{

	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
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
		EventDispatcher dispatcher(e);
		dispatcher.dispatchEvent<MouseScrolledEvent>(MH_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatchEvent<WindowResizeEvent>(MH_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		mZoomLevel -= e.getYOffset() * 0.5f;
		mZoomLevel = std::max(mZoomLevel, 0.25f);
		mCamera.setProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);

		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		mAspectRatio -= (float)e.getWidth() / (float)e.getHeight();
		mCamera.setProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);

		return false;
	}

}