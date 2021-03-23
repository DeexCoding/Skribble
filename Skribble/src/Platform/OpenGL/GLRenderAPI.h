#pragma once

#include "Skribble/Render/RenderAPI.h"

namespace Skribble
{
	class GLRenderAPI : public RenderAPI
	{
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void Clear(glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray, uint32_t indexCount) override;
	};
}