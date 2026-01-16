#include"yepch.h"
#include"Texture.h"

#include"Renderer.h"
#include"Platform/OpenGL/OpenGLTexture.h"

namespace YSJEN {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:YE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		YE_CORE_ASSERT(false, "Unknown RenderAPI!")
			return nullptr;
	}
}