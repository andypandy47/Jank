#include "Jankpch.h"
#include "Texture.h"

#include "Jank/Renderer/Renderer.h"
#include "Platform/OpenGl/OpenGLTexture.h"

namespace Jank
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	JANK_CORE_ASSERT(false, "RenderAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}

		JANK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}