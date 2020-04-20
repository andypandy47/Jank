#include "Jankpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Jank 
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		JANK_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JANK_CORE_ASSERT(status, "Failed to initialise Glad!");

		JANK_CORE_INFO("OpenGL Info:");
		JANK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		JANK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		JANK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}