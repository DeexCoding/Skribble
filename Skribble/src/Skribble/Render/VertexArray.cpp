#include "skpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/GLVertexArray.h"

namespace Skribble
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			return nullptr;

#if SKRIBBLE_WINDOWS

		case RenderAPIType::OpenGL:
			return new GLVertexArray();

#endif
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}
}