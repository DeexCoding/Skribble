#include "skpch.h"

#include "GLRenderAPI.h"

#include <glad/glad.h>

namespace Skribble
{
	void GLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void GLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void GLRenderAPI::Clear(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderAPI::DrawIndexed(const Ref<VertexArray>& _vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? _vertexArray->GetIndexBuffer()->GetCount() : indexCount; 
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}