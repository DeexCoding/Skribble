#include "skpch.h"

#include "RenderAPI.h"

namespace Skribble
{
#if SKRIBBLE_WINDOWS

	RenderAPIType RenderAPI::apiType = RenderAPIType::OpenGL;

#endif

}