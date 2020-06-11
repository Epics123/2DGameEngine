#include <Mayhem.h>

#include "imgui/imgui.h"

class ExampleLayer : public Mayhem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPos(0.0f, 0.0f, 0.0f)
	{
		mVertexArray.reset(Mayhem::VertexArray::create());

		float verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Mayhem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mayhem::VertexBuffer::create(verticies, sizeof(verticies)));

		Mayhem::BufferLayout layout = {
			{ Mayhem::ShaderDataType::Float3, "aPosition" },
			{ Mayhem::ShaderDataType::Float4, "aColor" }
		};

		vertexBuffer->setLayout(layout);

		mVertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indicies[3] = { 0, 1 , 2 };
		std::shared_ptr<Mayhem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mayhem::IndexBuffer::create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		mVertexArray->setIndexBuffer(indexBuffer);

		mSquareVA.reset(Mayhem::VertexArray::create());

		float squareVerticies[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Mayhem::VertexBuffer> squareVB;
		squareVB.reset(Mayhem::VertexBuffer::create(squareVerticies, sizeof(squareVerticies)));

		Mayhem::BufferLayout squareVBLayout = {
			{ Mayhem::ShaderDataType::Float3, "aPosition" }
		};

		squareVB->setLayout(squareVBLayout);

		mSquareVA->addVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Mayhem::IndexBuffer> squareIB;
		squareIB.reset(Mayhem::IndexBuffer::create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		mSquareVA->setIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			uniform mat4 uViewProj;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main()
			{
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = uViewProj * vec4(aPosition, 1.0);
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

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProj;

			out vec3 vPosition;
			
			void main()
			{
				vPosition = aPosition;
				gl_Position = uViewProj * vec4(aPosition, 1.0);
			}	
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}	
		)";

		mBlueShader.reset(Mayhem::Shader::create(blueShaderVertexSrc, blueShaderFragmentSrc));
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

		Mayhem::Renderer::submit(mBlueShader, mSquareVA);
		Mayhem::Renderer::submit(mShader, mVertexArray);

		Mayhem::Renderer::endScene();
	}

	void onEvent(Mayhem::Event& event)
	{

	}

private:
	std::shared_ptr<Mayhem::Shader> mShader;
	std::shared_ptr<Mayhem::VertexArray> mVertexArray;

	std::shared_ptr<Mayhem::VertexArray> mSquareVA;
	std::shared_ptr<Mayhem::Shader> mBlueShader;

	glm::vec3 mCameraPos;
	float mCameraRotation = 0.0f;
	
	float mCameraMovementSpeed = 3.0f;
	float mCameraRotationSpeed = 90.0f;

	Mayhem::OrthographicCamera mCamera;
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