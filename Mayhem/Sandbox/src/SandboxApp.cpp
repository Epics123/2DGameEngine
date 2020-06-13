#include <Mayhem.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"


class ExampleLayer : public Mayhem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPos(0.0f), mSquarePos(0.0f)
	{
		mVertexArray.reset(Mayhem::VertexArray::create());

		float verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Mayhem::Ref<Mayhem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mayhem::VertexBuffer::create(verticies, sizeof(verticies)));

		Mayhem::BufferLayout layout = {
			{ Mayhem::ShaderDataType::Float3, "aPosition" },
			{ Mayhem::ShaderDataType::Float4, "aColor" }
		};

		vertexBuffer->setLayout(layout);

		mVertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indicies[3] = { 0, 1 , 2 };
		Mayhem::Ref<Mayhem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mayhem::IndexBuffer::create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		mVertexArray->setIndexBuffer(indexBuffer);

		mSquareVA.reset(Mayhem::VertexArray::create());

		float squareVerticies[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Mayhem::Ref<Mayhem::VertexBuffer> squareVB;
		squareVB.reset(Mayhem::VertexBuffer::create(squareVerticies, sizeof(squareVerticies)));

		Mayhem::BufferLayout squareVBLayout = {
			{ Mayhem::ShaderDataType::Float3, "aPosition" }
		};

		squareVB->setLayout(squareVBLayout);

		mSquareVA->addVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		Mayhem::Ref<Mayhem::IndexBuffer> squareIB;
		squareIB.reset(Mayhem::IndexBuffer::create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		mSquareVA->setIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			uniform mat4 uViewProj;
			uniform mat4 uTransform;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main()
			{
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = uViewProj * uTransform * vec4(aPosition, 1.0);
			}
		
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			in vec4 vColor;
			
			void main()
			{
				color = vec4(vPosition * 0.5 + 0.5, 1.0);
				color = vColor;
			}
		
		)";

		mShader.reset(Mayhem::Shader::create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProj;
			uniform mat4 uTransform;

			out vec3 vPosition;
			
			void main()
			{
				vPosition = aPosition;
				gl_Position = uViewProj * uTransform * vec4(aPosition, 1.0);
			}	
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;

			uniform vec3 uColor;
			
			void main()
			{
				color = vec4(uColor, 1.0);
			}	
		)";

		mFlatColorShader.reset(Mayhem::Shader::create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void onUpdate(Mayhem::Timestep ts) override
	{
		if (Mayhem::Input::isKeyPressed(MH_KEY_LEFT))
			mCameraPos.x -= mCameraMovementSpeed * ts;
		else if (Mayhem::Input::isKeyPressed(MH_KEY_RIGHT))
			mCameraPos.x += mCameraMovementSpeed * ts;

		if (Mayhem::Input::isKeyPressed(MH_KEY_DOWN))
			mCameraPos.y -= mCameraMovementSpeed * ts;
		else if (Mayhem::Input::isKeyPressed(MH_KEY_UP))
			mCameraPos.y += mCameraMovementSpeed * ts;

		if (Mayhem::Input::isKeyPressed(MH_KEY_A))
			mCameraRotation += mCameraRotationSpeed * ts;
		else if (Mayhem::Input::isKeyPressed(MH_KEY_D))
			mCameraRotation -= mCameraRotationSpeed * ts;

		Mayhem::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mayhem::RenderCommand::clear();

		mCamera.setPostition(mCameraPos);
		mCamera.setRotation(mCameraRotation);

		Mayhem::Renderer::beginScene(mCamera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Mayhem::OpenGLShader>(mFlatColorShader)->bind();
		std::dynamic_pointer_cast<Mayhem::OpenGLShader>(mFlatColorShader)->uploadUniformFloat3("uColor", mSquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Mayhem::Renderer::submit(mFlatColorShader, mSquareVA, transform);
			}
		}
		Mayhem::Renderer::submit(mShader, mVertexArray);

		Mayhem::Renderer::endScene();
	}

	virtual void onImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
		ImGui::End();
	}

	void onEvent(Mayhem::Event& event) override
	{

	}

private:
	Mayhem::Ref<Mayhem::Shader> mShader;
	Mayhem::Ref<Mayhem::VertexArray> mVertexArray;

	Mayhem::Ref<Mayhem::VertexArray> mSquareVA;
	Mayhem::Ref<Mayhem::Shader> mFlatColorShader;

	Mayhem::OrthographicCamera mCamera;
	
	glm::vec3 mCameraPos;
	float mCameraRotation = 0.0f;
	
	float mCameraMovementSpeed = 2.0f;
	float mCameraRotationSpeed = 90.0f;

	glm::vec3 mSquarePos;
	float mSquareMoveSpeed = 1.0f;

	glm::vec3 mSquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Mayhem::Application

{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mayhem::Application* Mayhem::createApplication()
{
	return new Sandbox();
}