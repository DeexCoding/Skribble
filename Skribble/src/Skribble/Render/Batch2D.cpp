#include "skpch.h"

#include "Batch2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Skribble
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
		int flipX;
		int flipY;
		//TODO: MaskId
	};

	struct Batch2DData
	{
		static const uint32_t MaxQuadPerDraw = 10000;
		static const uint32_t MaxVerteciesPerDraw = MaxQuadPerDraw * 4;
		static const uint32_t MaxIndiciesPerDraw = MaxQuadPerDraw * 6;
		static const uint32_t MaxTextureSlots = 32; //TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Ref<Shader> CurrentShader;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 - WhiteTexture

		glm::vec4 QuadVertexPositions[4]{};
		int32_t samplers[MaxTextureSlots]{};
	};

	

	static Batch2DData* data;

	void Batch2D::Initalize()
	{
		data = new Batch2DData();

		data->QuadVertexArray = VertexArray::Create();
		data->QuadVertexBuffer = VertexBuffer::Create(data->MaxVerteciesPerDraw * sizeof(QuadVertex));
		data->QuadVertexBuffer->SetLayout(
			{
				{ ShaderDataType::Float3, "aPosition" },
				{ ShaderDataType::Float4, "aColor" },
				{ ShaderDataType::Float2, "aTexCoord" },
				{ ShaderDataType::Float, "aTexIndex" },
				{ ShaderDataType::Float, "aTilingFactor" },
				{ ShaderDataType::Int, "aFlipX" },
				{ ShaderDataType::Int, "aFlipY" }
			});

		data->QuadVertexArray->AddVertexBuffer(data->QuadVertexBuffer);

		data->QuadVertexBufferBase = new QuadVertex[data->MaxVerteciesPerDraw];

		uint32_t* quadIndicies = new uint32_t[data->MaxIndiciesPerDraw];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < data->MaxIndiciesPerDraw; i += 6)
		{
			quadIndicies[i + 0] = offset + 0;
			quadIndicies[i + 1] = offset + 1;
			quadIndicies[i + 2] = offset + 2;

			quadIndicies[i + 3] = offset + 2;
			quadIndicies[i + 4] = offset + 3;
			quadIndicies[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndicies, data->MaxIndiciesPerDraw);
		data->QuadVertexArray->SetIndexBuffer(quadIB);

		delete[] quadIndicies;

		data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		for (int32_t i = 0; i < data->MaxTextureSlots; i++)
		{
			data->samplers[i] = i;
		}

		data->TextureSlots[0] = data->WhiteTexture;

		data->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		data->QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Batch2D::Shutdown()
	{
		delete data;
	}
	
	void Batch2D::AddSamplers(Ref<Shader> shader)
	{
		shader->Bind();
		shader->SetIntArray("uTextures", data->samplers, data->MaxTextureSlots);
	}

	void Batch2D::Begin(const Camera& camera, Ref<Shader> shader)
	{
		shader->Bind();
		shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

		data->CurrentShader = shader;

		NewBatch();
	}

	void Batch2D::End()
	{
		Flush();
		data->CurrentShader->Unbind();
	}

	void Batch2D::Flush()
	{
		if (data->QuadIndexCount == 0)
		{
			return; // Nothing to draw
		}

		uint32_t dataSize = (uint32_t)((uint8_t*)data->QuadVertexBufferPtr - (uint8_t*)data->QuadVertexBufferBase);
		data->QuadVertexBuffer->SetData(data->QuadVertexBufferBase, dataSize);

		// Bind textures
		for (uint32_t i = 0; i < data->TextureSlotIndex; i++)
		{
			data->TextureSlots[i]->Bind(i);
		}

		data->CurrentShader->Bind();
		Renderer::DrawIndexed(data->QuadVertexArray, data->QuadIndexCount);
	}

	void Batch2D::NewBatch()
	{
		data->QuadIndexCount = 0;
		data->QuadVertexBufferPtr = data->QuadVertexBufferBase;

		data->TextureSlotIndex = 1;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="sortingLayer"></param>
	/// <param name="rotation">In degrees</param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	/// <param name="texture">nullptr if no texture is applied</param>
	/// <param name="tilingFactor">1 for no tiling</param>
	/// <param name="flipX"></param>
	/// <param name="flipY"></param>
	void Batch2D::DrawQuad(const glm::vec2& position, float sortingLayer, float rotation, const glm::vec2& size,
		const glm::vec4& color, const Ref<Texture2D> texture, float tilingFactor, bool flipX, bool flipY)
	{
		if (data->QuadIndexCount >= Batch2DData::MaxIndiciesPerDraw)
		{
			Flush();
			NewBatch();
		}

		float textureIndex = 0.0f;

		if (texture != nullptr)
		{
			for (uint32_t i = 1; i < data->TextureSlotIndex; i++)
			{
				if (*data->TextureSlots[i] == *texture)
				{
					textureIndex = (float)i;
					break;
				}
			}

			if (textureIndex == 0.0f)
			{
				if (data->TextureSlotIndex >= Batch2DData::MaxTextureSlots)
				{
					Flush();
					NewBatch();
				}

				textureIndex = data->TextureSlotIndex;
				data->TextureSlots[data->TextureSlotIndex] = texture;
				data->TextureSlotIndex++;
			}
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, sortingLayer });

		if (rotation != 0.0f)
		{
			transform *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
		}

		if (size.x != 1.0f || size.y != 1.0f)
		{
			transform *= glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });
		}

		data->QuadVertexBufferPtr->Position = transform * data->QuadVertexPositions[0];
		data->QuadVertexBufferPtr->Color = color;
		data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		data->QuadVertexBufferPtr->TexIndex = textureIndex;
		data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		data->QuadVertexBufferPtr->flipX = flipX;
		data->QuadVertexBufferPtr->flipY = flipY;
		data->QuadVertexBufferPtr++;

		data->QuadVertexBufferPtr->Position = transform * data->QuadVertexPositions[1];
		data->QuadVertexBufferPtr->Color = color;
		data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		data->QuadVertexBufferPtr->TexIndex = textureIndex;
		data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		data->QuadVertexBufferPtr->flipX = flipX;
		data->QuadVertexBufferPtr->flipY = flipY;
		data->QuadVertexBufferPtr++;

		data->QuadVertexBufferPtr->Position = transform * data->QuadVertexPositions[2];
		data->QuadVertexBufferPtr->Color = color;
		data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		data->QuadVertexBufferPtr->TexIndex = textureIndex;
		data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		data->QuadVertexBufferPtr->flipX = flipX;
		data->QuadVertexBufferPtr->flipY = flipY;
		data->QuadVertexBufferPtr++;

		data->QuadVertexBufferPtr->Position = transform * data->QuadVertexPositions[3];
		data->QuadVertexBufferPtr->Color = color;
		data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		data->QuadVertexBufferPtr->TexIndex = textureIndex;
		data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		data->QuadVertexBufferPtr->flipX = flipX;
		data->QuadVertexBufferPtr->flipY = flipY;
		data->QuadVertexBufferPtr++;

		data->QuadIndexCount += 6;
	}

	void Batch2D::DrawText(const glm::vec2& position, float sortingLayer, float rotation, const glm::vec2& size,
		const glm::vec4& color, const Ref<Font> font, std::string text)
	{
		glm::vec2 pen = position;

		for (int i = 0; i < text.size(); i++)
		{
			Character c = font->GetCharacter(text[i]);
		
			float x = pen.x + c.bearing.x * size.x;
			float y = pen.y - (c.size.y - c.bearing.y) * size.y;
		
			float width = c.size.x * size.x;
			float height = c.size.y * size.y;
		
			Batch2D::DrawQuad({ x, y }, sortingLayer, rotation, { width, height }, color, c.texture, 1.0f,
				false, true);
		
			pen.x += (c.advance.x >> 6) * size.x;
			pen.y += (c.advance.y >> 6) * size.y;
		}
	}
}