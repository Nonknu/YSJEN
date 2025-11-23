#pragma once

#ifdef  YE_PLATFORM_WINDOWS
	
extern	YSJEN::Application*  YSJEN::CreatApplication();

int main(int argc, char** argv) {

	YSJEN::Log::Init();
	YE_CORE_WARN("Initialize Log!");
	int a = 5;
	YE_INFO("Hello! var={0}",a);


	auto app = YSJEN::CreatApplication();
	app->Run();
	delete app;
}
#endif // 
