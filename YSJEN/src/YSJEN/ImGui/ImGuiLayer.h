#pragma once

#include "YSJEN/Layer.h"
#include "YSJEN/Events/KeyEvent.h"
#include "YSJEN/Events/MouseEvent.h"
#include "YSJEN/Events/ApplicationEvent.h"

namespace YSJEN {

	class YSJEN_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}