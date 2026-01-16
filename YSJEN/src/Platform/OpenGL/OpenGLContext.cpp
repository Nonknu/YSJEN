#include"yepch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<GLAD/glad.h>
namespace YSJEN {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHndle(windowHandle)
	{
		YE_CORE_ASSERT(windowHandle,"Window handle is null")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHndle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		YE_CORE_ASSERT(status, "Failed to initialize Glad");

		YE_CORE_INFO("OpenGL info: ");
		YE_CORE_INFO("Vendor: {0} ", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		YE_CORE_INFO("Renderer: {0} ", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		YE_CORE_INFO("Version: {0} ", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHndle);
	}
}