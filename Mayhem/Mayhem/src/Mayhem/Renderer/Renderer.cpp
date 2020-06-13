#include "mpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Mayhem
{
	Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData;

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