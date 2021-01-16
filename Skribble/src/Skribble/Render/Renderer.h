#pragma once

#include "RenderAPI.h"

#include "Camera.h"
#include "Shader.h"

namespace Skribble
{
	class Renderer
	{
	public:
		static void Init();

		static void Begin(Camera& camera);
		static void End();

		static void Submit(const Ref<VertexArray>& _vertexArray, const Ref<Shader>& _shader,
			const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPIType GetAPI() { return RenderAPI::GetAPIType(); }

		inline static void Clear(glm::vec4& color)
		{
			api->Clear(color);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& _vertexArray)
		{
			api->DrawIndexed(_vertexArray);
		}

	private:
		struct RendererData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static RendererData* data;
		static RenderAPI* api;
	};

}