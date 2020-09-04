#include "skpch.h"
#include "Renderer.h"

namespace Skribble
{
	void Renderer::Begin()
	{

	}

	void Renderer::End()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& _vertexArray)
	{
		_vertexArray->Bind();
		RenderCommand::DrawIndexed(_vertexArray);
	}
}