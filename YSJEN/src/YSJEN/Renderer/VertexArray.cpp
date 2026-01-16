#include "yepch.h"
#include"VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace YSJEN {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:YE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		YE_CORE_ASSERT(false, "Unknown RenderAPI!")
			return nullptr;
	}
}