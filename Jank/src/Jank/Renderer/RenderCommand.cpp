#include "Jankpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace Jank
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}