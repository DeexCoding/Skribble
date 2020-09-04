#include "skpch.h"

#include "../Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#if SKRIBBLE_WINDOWS
#include "Platform/OpenGL/GLVertexBuffer.h"
#include "Platform/OpenGL/GLIndexBuffer.h"
#endif
#include "Renderer.h"

namespace Skribble
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			return nullptr;

#if SKRIBBLE_WINDOWS

		case RenderAPIType::OpenGL:
			return new GLVertexBuffer(vertices, size);
		
#endif
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			return nullptr;

#if SKRIBBLE_WINDOWS

		case RenderAPIType::OpenGL:
			return new GLIndexBuffer(indices, size);

#endif
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}
}