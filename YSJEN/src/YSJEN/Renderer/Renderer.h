#pragma once
#include"RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
namespace YSJEN {

	class Renderer {

	public:
		static void Init();

		static void BeginScene();
		static void BeginScene(Camera& camera);

		static void EndScene();

		static void Submit(const Ref<VertexArray>&vertexArray, const Ref<Shader>&shader,const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;  
		};

		static SceneData* s_SceneData;  
	};
}