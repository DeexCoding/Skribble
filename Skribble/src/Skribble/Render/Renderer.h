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
		
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Begin(Camera& camera);
		static void End();

		static void Submit(const Ref<VertexArray>& _vertexArray, const Ref<Shader>& _shader,
			const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPIType GetAPI() { return RenderAPI::GetAPIType(); }

		inline static void Clear(glm::vec4& color)
		{
			api->Clear(color);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& _vertexArray, uint32_t count = 0)
		{
			api->DrawIndexed(_vertexArray, count);
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