#include <Mayhem.h>
#include <Mayhem/Core/EntryPoint.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"


class ExampleLayer : public Mayhem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), mCameraController(1280.0f / 720.0f)
	{
		
	}

	void onUpdate(Mayhem::Timestep ts) override
	{
		//Update
		mCameraController.onUpdate(ts);

		//Render
		Mayhem::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mayhem::RenderCommand::clear();

		Mayhem::Renderer::beginScene(mCameraController.getCamera());

		Mayhem::Renderer::endScene();
	}

	virtual void onImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
		ImGui::End();
	}

	void onEvent(Mayhem::Event& e) override
	{
		//mCameraController.onEvent(e);
	}

private:
	Mayhem::ShaderLibrary mShaderLibrary;
	Mayhem::Ref<Mayhem::Shader> mShader;
	Mayhem::Ref<Mayhem::VertexArray> mVertexArray;

	Mayhem::Ref<Mayhem::VertexArray> mSquareVA;
	Mayhem::Ref<Mayhem::Shader> mFlatColorShader;

	Mayhem::Ref<Mayhem::Texture2D> mTexture, mClassicSonicTexture;

	Mayhem::OrthographicCameraController mCameraController;
	glm::vec3 mSquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Mayhem::Application

{
public:
	Sandbox()
	{
		//pushLayer(new ExampleLayer());
		//pushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Mayhem::Application* Mayhem::createApplication()
{
	return new Sandbox();
}