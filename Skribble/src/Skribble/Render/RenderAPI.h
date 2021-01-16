#pragma once

#include <glm/glm.hpp>
#include "../Core.h"
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

		virtual void Clear(glm::vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& _vertexArray) = 0;

		inline static RenderAPIType GetAPIType() { return apiType; }

	private:
		static RenderAPIType apiType;

	};
}