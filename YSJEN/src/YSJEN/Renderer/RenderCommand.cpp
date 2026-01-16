#include "yepch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace YSJEN {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}