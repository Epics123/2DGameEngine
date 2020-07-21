#pragma once

#include "Mayhem.h"


class Sandbox2D : public Mayhem::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void onAttatch() override;
	virtual void onDetatch() override;

	void onUpdate(Mayhem::Timestep ts) override;
	void onEvent(Mayhem::Event& e) override;
	virtual void onImGuiRender() override;

private:
	Mayhem::OrthographicCameraController mCameraController;
	//Temp
	Mayhem::Ref<Mayhem::Shader> mFlatColorShader;
	Mayhem::Ref<Mayhem::VertexArray> mSquareVA;

	Mayhem::Ref<Mayhem::Texture2D> mTailsTexture;
	Mayhem::Ref<Mayhem::Texture2D> mSpriteSheet;
	Mayhem::Ref<Mayhem::SubTexture2D> mTextureStairs;
	
	glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
