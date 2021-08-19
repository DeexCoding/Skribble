#include "skpch.h"
#include "Renderer.h"

#include "Batch2D.h"

#include "Platform/OpenGL/GLShader.h"
#include "Platform/OpenGL/GLRenderAPI.h"

namespace Skribble
{
	Renderer::RendererData* Renderer::data = new Renderer::RendererData;

#ifdef SKRIBBLE_WINDOWS

	RenderAPI* Renderer::api = new GLRenderAPI;
	
#endif

	void Renderer::Init()
	{
		SKRIBBLE_PROFILE_SCOPE("Renderer::Init");

		api->Init();

		Batch2D::Initalize();
	}

	void Renderer::Begin(OrthographicCamera& camera)
	{
		data->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::End()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		api->SetViewport(0, 0, width, height);
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