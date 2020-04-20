#include "Jankpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGl/OpenGLBuffer.h"

namespace Jank
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		JANK_CORE_ASSERT(false, "RenderAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		JANK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		JANK_CORE_ASSERT(false, "RenderAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		JANK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}