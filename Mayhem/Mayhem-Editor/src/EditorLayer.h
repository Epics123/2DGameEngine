#pragma once

#include "Mayhem.h"

namespace Mayhem
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void onAttatch() override;
		virtual void onDetatch() override;

		void onUpdate(Timestep ts) override;
		void onEvent(Event& e) override;
		virtual void onImGuiRender() override;

	private:
		OrthographicCameraController mCameraController;
		//Temp
		Ref<Shader> mFlatColorShader;
		Ref<VertexArray> mSquareVA;
		Ref<FrameBuffer> mFrameBuffer;

		Ref<Scene> mActiveScene;
		Entity mSquareEntity;
		Entity mCameraEntity;
		Entity mSecondCamera;

		bool mPrimaryCamera = true;

		Ref<Texture2D> mTailsTexture;
		Ref<Texture2D> mSpriteSheet;
		Ref<SubTexture2D> mTextureStairs;
		Ref<SubTexture2D> mTextureTree;

		bool mViewportFocused = false, mViewportHovered = false;
		glm::vec2 mViewportSize = { 0, 0 };

		glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}
