#include "mpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mayhem
{

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		//TODO:   texid
	};

	struct Renderer2DData
	{
		const uint32_t MAX_QUADS = 10000;
		const uint32_t MAX_VERTICIES = MAX_QUADS * 4;
		const uint32_t MAX_INDICIES = MAX_QUADS * 6;


		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;
	};

	static Renderer2DData sData;

	void Renderer2D::init()
	{
		MH_PROFILE_FUNCTION();

		sData.quadVertexArray = VertexArray::create();

		sData.quadVertexBuffer = VertexBuffer::create(sData.MAX_VERTICIES * sizeof(QuadVertex));
		sData.quadVertexBuffer->setLayout({
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" },
		});
		sData.quadVertexArray->addVertexBuffer(sData.quadVertexBuffer);

		sData.quadVertexBufferBase = new QuadVertex[sData.MAX_VERTICIES];

		uint32_t* quadIndicies = new uint32_t[sData.MAX_INDICIES];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < sData.MAX_INDICIES; i += 6)
		{
			quadIndicies[i + 0] = offset + 0;
			quadIndicies[i + 1] = offset + 1;
			quadIndicies[i + 2] = offset + 2;

			quadIndicies[i + 3] = offset + 2;
			quadIndicies[i + 4] = offset + 3;
			quadIndicies[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::create(quadIndicies, sData.MAX_INDICIES);
		sData.quadVertexArray->setIndexBuffer(quadIB);
		delete[] quadIndicies;

		uint32_t whiteTextureData = 0xffffffff;
		sData.whiteTexture = Texture2D::create(1, 1);

		sData.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		sData.textureShader = Shader::create("assets/shaders/Texture.glsl");
		sData.textureShader->bind();
		sData.textureShader->setInt("uTexture", 0);
	}

	void Renderer2D::shutdown()
	{
		MH_PROFILE_FUNCTION();
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera)
	{
		MH_PROFILE_FUNCTION();

		sData.textureShader->bind();
		sData.textureShader->setMat4("uViewProj", camera.getViewProjMatrix());

		sData.quadIndexCount = 0;
		sData.quadVertexBufferPtr = sData.quadVertexBufferBase;
	}

	void Renderer2D::endScene()
	{
		MH_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)sData.quadVertexBufferPtr - (uint8_t*)sData.quadVertexBufferBase;
		sData.quadVertexBuffer->setData(sData.quadVertexBufferBase, dataSize);

		flush();
	}

	void Renderer2D::flush()
	{
		RenderCommand::drawIndexed(sData.quadVertexArray, sData.quadIndexCount);
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		MH_PROFILE_FUNCTION();

		sData.quadVertexBufferPtr->Position = position;
		sData.quadVertexBufferPtr->Color = color;
		sData.quadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		sData.quadVertexBufferPtr++;

		sData.quadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		sData.quadVertexBufferPtr->Color = color;
		sData.quadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		sData.quadVertexBufferPtr++;

		sData.quadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		sData.quadVertexBufferPtr->Color = color;
		sData.quadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		sData.quadVertexBufferPtr++;

		sData.quadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		sData.quadVertexBufferPtr->Color = color;
		sData.quadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		sData.quadVertexBufferPtr++;

		sData.quadIndexCount += 6;

		/*sData.textureShader->setFloat("uTilingFactor", 1.0f);
		sData.whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		sData.textureShader->setMat4("uTransform", transform);

		sData.quadVertexArray->bind();
		RenderCommand::drawIndexed(sData.quadVertexArray);*/
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MH_PROFILE_FUNCTION();

		sData.textureShader->setFloat4("uColor", tintColor);
		sData.textureShader->setFloat("uTilingFactor", tilingFactor);
		sData.textureShader->bind();

		texture->bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		sData.textureShader->setMat4("uTransform", transform);

		sData.quadVertexArray->bind();
		RenderCommand::drawIndexed(sData.quadVertexArray);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		drawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		MH_PROFILE_FUNCTION();

		sData.textureShader->setFloat4("uColor", color);
		sData.textureShader->setFloat("uTilingFactor", 1.0f);
		sData.whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		sData.textureShader->setMat4("uTransform", transform);

		sData.quadVertexArray->bind();
		RenderCommand::drawIndexed(sData.quadVertexArray);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		drawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4 & tintColor)
	{
		MH_PROFILE_FUNCTION();

		sData.textureShader->setFloat4("uColor", tintColor);
		sData.textureShader->setFloat("uTilingFactor", tilingFactor);
		sData.textureShader->bind();

		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		sData.textureShader->setMat4("uTransform", transform);

		sData.quadVertexArray->bind();
		RenderCommand::drawIndexed(sData.quadVertexArray);
	}

}