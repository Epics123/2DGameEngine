#include "mpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Mayhem
{
	Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

	void Renderer::init()
	{
		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::shutdown()
	{
		Renderer2D::shutdown();
	}

	void Renderer::onWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::setViewport(0, 0, width, height);
	}

	void Renderer::beginScene(OrthographicCamera& camera)
	{
		mSceneData->ViewProjMatrix = camera.getViewProjMatrix();
	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("uViewProj", mSceneData->ViewProjMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("uTransform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}