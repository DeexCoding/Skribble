#include "skpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/GLRenderAPI.h"

namespace Skribble
{
	RenderAPI* RenderCommand::api = new GLRenderAPI;
}