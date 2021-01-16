#include "skpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/GLShader.h"
#include "Platform/OpenGL/GLRenderAPI.h"

namespace Skribble
{
	Renderer::RendererData* Renderer::data = new Renderer::RendererData;

	RenderAPI* Renderer::api = new GLRenderAPI;

	void Renderer::Init()
	{
		api->Init();
	}

	void Renderer::Begin(Camera& camera)
	{
		data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::End()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& _vertexArray, const Ref<Shader>& _shader, 
		const glm::mat4& transform)
	{
		_shader->Bind();
		_shader->SetMat4("u_viewProjection", data->ViewProjectionMatrix);
		_shader->SetMat4("u_transform", transform);

		_vertexArray->Bind();

		DrawIndexed(_vertexArray);
	}
}