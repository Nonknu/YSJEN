#pragma once
#include"yepch.h"

#include "Core.h"

#include "Window.h"
#include "YSJEN/LayerStack.h"
#include "Events/Event.h"
#include "YSJEN/Events/ApplicationEvent.h"

#include "YSJEN/Core/Timestep.h"

#include "YSJEN/ImGui/ImGuiLayer.h"
#include "YSJEN/Renderer/Shader.h"
#include "YSJEN/Renderer/Buffer.h"
#include "YSJEN/Renderer/VertexArray.h"
#include "YSJEN/Renderer/Camera.h"
namespace YSJEN {
	class YSJEN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer); 

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//to be define in client
	Application* CreatApplication();
}


