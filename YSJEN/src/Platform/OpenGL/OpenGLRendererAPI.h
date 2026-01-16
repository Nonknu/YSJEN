#pragma once

#include"YSJEN/Renderer/RendererAPI.h"

namespace YSJEN {
	class OpenGLRendererAPI :public RendererAPI {
	public:
		virtual void Init()override;
		virtual void SetClearColor(const glm::vec4& color)override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray)override;
	};
}