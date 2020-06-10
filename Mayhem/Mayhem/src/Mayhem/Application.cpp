#include "mpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace Mayhem
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sInstance = nullptr;

	Application::Application()
	{
		MH_CORE_ASSERT(!sInstance, "Application already exists!");
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::createWindow());
		mWindow->setEventCallback(BIND_EVENT_FN(onEvent));

		mImGuiLayer = new ImGuiLayer();
		pushOverlay(mImGuiLayer);

		mVertexArray.reset(VertexArray::create());

		float verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::create(verticies, sizeof(verticies)));
		//mVertexBuffer->bind();

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" }
		};
			
		vertexBuffer->setLayout(layout);

		mVertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indicies[3] = { 0, 1 , 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::create(indicies, sizeof(indicies) / sizeof(uint32_t)));
		mVertexArray->setIndexBuffer(indexBuffer);

		mSquareVA.reset(VertexArray::create());

		float squareVerticies[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB; 
		squareVB.reset(VertexBuffer::create(squareVerticies, sizeof(squareVerticies)));

		BufferLayout squareVBLayout = {
			{ ShaderDataType::Float3, "aPosition" }
		};

		squareVB->setLayout(squareVBLayout);

		mSquareVA->addVertexBuffer(squareVB);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		mSquareVA->setIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main()
			{
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = vec4(aPosition, 1.0);
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

		mShader.reset(Shader::create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			out vec3 vPosition;
			
			void main()
			{
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 1.0);
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

		mBlueShader.reset(Shader::create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (mRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			mBlueShader->bind();
			mSquareVA->bind();
			glDrawElements(GL_TRIANGLES, mSquareVA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			mShader->bind();
			mVertexArray->bind();
			glDrawElements(GL_TRIANGLES, mVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : mLayerStack)
				layer->onUpdate();

			mImGuiLayer->begin();
			for (Layer* layer : mLayerStack)
				layer->onImGuiRender();
			mImGuiLayer->end();

			mWindow->onUpdate();
		}
	}

	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatchEvent<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.mHandled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		mLayerStack.pushLayer(layer);
		layer->onAttatch();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		mLayerStack.pushLayer(overlay);
		overlay->onAttatch();
	}

	bool Application::onWindowClosed(WindowCloseEvent& event)
	{
		mRunning = false;
		return true;
	}
}