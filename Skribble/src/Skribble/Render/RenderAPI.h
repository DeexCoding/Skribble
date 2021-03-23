#pragma once

#include <glm/glm.hpp>
#include "../Core/Core.h"
#include "VertexArray.h"

namespace Skribble
{
	enum class RenderAPIType
	{
		None = 0,
		OpenGL = 1
	};

	class RenderAPI
	{
	public:
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void Clear(glm::vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray, uint32_t indexCount) = 0;

		inline static RenderAPIType GetAPIType() { return apiType; }

	private:
		static RenderAPIType apiType;

	};
}