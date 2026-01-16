#include "yepch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "PlatForm/OpenGL/OpenGLBuffer.h"
namespace YSJEN {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:YE_CORE_ASSERT(false,"RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices,size);
		}
		YE_CORE_ASSERT(false, "Unknown RenderAPI!")
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:YE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		YE_CORE_ASSERT(false, "Unknown RenderAPI!")
			return nullptr;
	}
}