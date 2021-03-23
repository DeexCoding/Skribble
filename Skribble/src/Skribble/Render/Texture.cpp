#include "skpch.h"

#include "../Core/Core.h"

#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/GLTexture.h"

namespace Skribble
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");
			return nullptr;

#if SKRIBBLE_WINDOWS

		case RenderAPIType::OpenGL:
			return CreateRef<GLTexture2D>(width, height);

#endif
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPIType::None:
			SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");
			return nullptr;

#if SKRIBBLE_WINDOWS

		case RenderAPIType::OpenGL:
			return CreateRef<GLTexture2D>(path);

#endif
		}

		SKRIBBLE_CORE_ASSERT(false, "Unknown rendering API!");

		return nullptr;
	}
}