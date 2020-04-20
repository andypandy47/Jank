#pragma once

#include "Jank/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Jank
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}