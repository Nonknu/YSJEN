#include"YSJEN.h"
#include<imgui/imgui.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "YSJEN/Input.h"

class Examplayer:public YSJEN::Layer
{
public:
	Examplayer()
		:Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f, 1.0f, -1.0f)
	{	
		auto& window = YSJEN::Application::Get().GetWindow();
		float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();
		float height = 0.9f;
		float width = height * aspectRatio;
		m_Camera.SetOrthographicBounds(-width, width, -height, height);
		///////////////////////////////////////////////////////////////
		m_CameraController.setCamera(&m_Camera);
		///////////////////////////////////////////////////////////////
		m_VertexArray.reset(YSJEN::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		YSJEN::Ref<YSJEN::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(YSJEN::VertexBuffer::Create(vertices, sizeof(vertices)));
		YSJEN::BufferLayout layout = {
			{ YSJEN::ShaderDataType::Float3, "a_Position" },
			{YSJEN::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		YSJEN::Ref<YSJEN::IndexBuffer> indexBuffer;
		indexBuffer.reset(YSJEN::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(YSJEN::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-1.0f, -1.0f, 0.0f,0.0f,0.0f,
			 1.0f, -1.0f, 0.0f,1.0f,0.0f,
			 1.0f,  1.0f, 0.0f,1.0f,1.0f,
			-1.0f,  1.0f, 0.0f,0.0f,1.0f,
		};

		YSJEN::Ref<YSJEN::VertexBuffer> squareVB;
		squareVB.reset(YSJEN::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ YSJEN::ShaderDataType::Float3, "a_Position" },
			{ YSJEN::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		YSJEN::Ref<YSJEN::IndexBuffer> squareIB;
		squareIB.reset(YSJEN::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;  
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position; 
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = YSJEN::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);


		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection; 
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1.0);		
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
		
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_FlatColorShader = YSJEN::Shader::Create("assets/shaders/shadertoy1.glsl");

		auto m_TextureShader=m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture=YSJEN::Texture2D::Create("assets/textures/Checkerboard.png");
		m_CTexture = YSJEN::Texture2D::Create("assets/textures/man.png");
		std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_TextureShader)->UpUniformInt("u_Texture", 0);
	}

	void OnUpdate(YSJEN::Timestep ts)override {

		m_Time += ts;

		m_CameraController.OnUpdate(ts);
		YSJEN::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		YSJEN::RenderCommand::Clear();

		YSJEN::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f),glm::vec3(1.1f));

		std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_FlatColorShader)->Bind();
		
		// 设置 shadertoy1.glsl 所需的 uniform 变量
		auto& window = YSJEN::Application::Get().GetWindow();
		glm::vec2 resolution((float)window.GetWidth(), (float)window.GetHeight());
		std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_FlatColorShader)->UpUniformFloat2("u_resolution", resolution);
		std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_FlatColorShader)->UpUniformFloat1("u_time", m_Time);
		
		// 获取鼠标位置
		auto [mouseX, mouseY] = YSJEN::Input::GetMousePosition();
		glm::vec4 mouse(mouseX, mouseY, mouseX, mouseY); // xy=当前鼠标位置, zw=点击位置（暂时设为相同）
		// std::dynamic_pointer_cast<YSJEN::OpenGLShader>(m_FlatColorShader)->UpUniformFloat4("u_mouse", mouse);
		
		for (int y = 0; y < 1;y++) {
				for (int x = 0; x < 1; x++) {
					glm::vec3 pos(x ,y,0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale;
					YSJEN::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
				}
		}
		m_Texture->Bind();
		//YSJEN::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//YSJEN::Renderer::Submit(m_VertexArray, m_Shader);
		m_CTexture->Bind();
		//YSJEN::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//YSJEN::Renderer::Submit(m_VertexArray, m_Shader);

		YSJEN::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		//ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(YSJEN::Event& event)override {
		//	YE_TRACE("{}", event.ToString());

	}
private:
	YSJEN::ShaderLibrary m_ShaderLibrary;
	YSJEN::Ref<YSJEN::Shader> m_Shader;
	YSJEN::Ref<YSJEN::VertexArray>m_VertexArray;

	YSJEN::Ref<YSJEN::Shader> m_FlatColorShader;
	YSJEN::Ref<YSJEN::VertexArray> m_SquareVA;

	YSJEN::Ref<YSJEN::Texture2D> m_Texture, m_CTexture;

	YSJEN::Camera m_Camera;

	YSJEN::CameraController m_CameraController;

	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.3f, 0.8f);
	
	float m_Time = 0.0f; // 累积时间，用于 shadertoy 着色器
};



class SandBox : public YSJEN::Application {
public:
	SandBox() {
		PushLayer(new Examplayer());

	}

	~SandBox() {
	
	}
};

YSJEN::Application* YSJEN::CreatApplication() {
	return new SandBox();
}