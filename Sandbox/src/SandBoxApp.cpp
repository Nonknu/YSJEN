#include"YSJEN.h"

class Examplayer:public YSJEN::Layer
{
public:
	Examplayer()
		:Layer("Example")
	{
	}
	void OnUpdate()override {
		YE_INFO("ExampleLayer::Update");
	}

	void OnEvent(YSJEN::Event& event)override {
		YE_TRACE("{}", event.ToString());

	}
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