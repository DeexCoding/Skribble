#pragma once

#include "RenderAPI.h"
#include "RenderCommand.h"

namespace Skribble
{
	class Renderer
	{
	public:
		static void Begin();
		static void End();

		static void Submit(const Ref<VertexArray>& _vertexArray);

		inline static RenderAPIType GetAPI() { return RenderAPI::GetAPIType(); }

	};

}