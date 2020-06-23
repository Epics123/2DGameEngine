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
	mTailsTexture = Mayhem::Texture2D::create("assets/textures/Tails.png");
}

void Sandbox2D::onDetatch()
{

}

void Sandbox2D::onUpdate(Mayhem::Timestep ts)
{
	//Update
	mCameraController.onUpdate(ts);

	//Render
	Mayhem::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Mayhem::RenderCommand::clear();

	Mayhem::Renderer2D::beginScene(mCameraController.getCamera());
	
	Mayhem::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Mayhem::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Mayhem::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, mTailsTexture);
	Mayhem::Renderer2D::endScene();
}

void Sandbox2D::onEvent(Mayhem::Event& e)
{
	mCameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}
