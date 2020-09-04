#include "skpch.h"

#include "GLRenderAPI.h"

#include <glad/glad.h>

namespace Skribble
{
	void GLRenderAPI::Clear(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderAPI::DrawIndexed(const Ref<VertexArray>& _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}