#include "mpch.h"
#include "Renderer.h"

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

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->bind();
		shader->uploadUniformMat4("uViewProj", mSceneData->ViewProjMatrix);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}