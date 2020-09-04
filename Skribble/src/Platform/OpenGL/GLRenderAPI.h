#pragma once

#include "Skribble/Render/RenderAPI.h"

namespace Skribble
{
	class GLRenderAPI : public RenderAPI
	{
		virtual void Clear(glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray) override;
	};
}