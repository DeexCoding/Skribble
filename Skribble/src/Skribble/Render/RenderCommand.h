#pragma once

#include "RenderAPI.h"

namespace Skribble
{
	class RenderCommand
	{
	public:
		inline static void Clear(glm::vec4& color)
		{
			api->Clear(color);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& _vertexArray)
		{
			api->DrawIndexed(_vertexArray);
		}

	private:
		static RenderAPI* api;
	};
}