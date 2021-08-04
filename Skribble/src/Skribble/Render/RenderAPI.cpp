#include "skpch.h"

#include "RenderAPI.h"

namespace Skribble
{
#ifdef SKRIBBLE_WINDOWS

	RenderAPIType RenderAPI::apiType = RenderAPIType::OpenGL;

#endif

}