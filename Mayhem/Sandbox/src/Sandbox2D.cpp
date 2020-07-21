#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sandox2D"), mCameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::onAttatch()
{
	MH_PROFILE_FUNCTION();

	mTailsTexture = Mayhem::Texture2D::create("assets/textures/Tails.png");
	mSpriteSheet = Mayhem::Texture2D::create("assets/game/textures/RPGpack_sheet_2X.png");

	mTextureStairs = Mayhem::SubTexture2D::createFromCoords(mSpriteSheet, { 7, 6 }, { 128, 128 });
}

void Sandbox2D::onDetatch()
{
	MH_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(Mayhem::Timestep ts)
{
	MH_PROFILE_FUNCTION();

	//Update
	mCameraController.onUpdate(ts);

	//Render
	Mayhem::Renderer2D::resetStats();
	{
		MH_PROFILE_SCOPE("Render Prep");
		Mayhem::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mayhem::RenderCommand::clear();
	}
	
	{
		MH_PROFILE_SCOPE("Render Draw");

		static float rotation = 0.0f;
		static float texRotation = 0.0f;
		rotation += ts * 20.0f;
		texRotation += ts * -50.0f;

		Mayhem::Renderer2D::beginScene(mCameraController.getCamera());
		Mayhem::Renderer2D::drawRotatedQuad({ 1.2f, 0.0f }, { 0.8f, 0.8f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Mayhem::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f },  { 0.8f, 0.2f, 0.3f, 1.0f });
		Mayhem::Renderer2D::drawQuad({ 0.5f, -1.0f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Mayhem::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, mTailsTexture);
		Mayhem::Renderer2D::drawRotatedQuad({ 2.5f, 0.0f, 0.0f }, { 1.0f, 1.0f },  texRotation, mTailsTexture);
		Mayhem::Renderer2D::endScene();

		Mayhem::Renderer2D::beginScene(mCameraController.getCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 0.5f) / 10.0f, 0.4f, (y + 0.5f) / 10.0f, 0.7f };
				Mayhem::Renderer2D::drawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Mayhem::Renderer2D::endScene();

		Mayhem::Renderer2D::beginScene(mCameraController.getCamera());
		Mayhem::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, mTextureStairs);
		Mayhem::Renderer2D::endScene();
	}
}

void Sandbox2D::onEvent(Mayhem::Event& e)
{
	mCameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
	MH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Mayhem::Renderer2D::getStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
	ImGui::Text("Indices: %d", stats.getTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}
