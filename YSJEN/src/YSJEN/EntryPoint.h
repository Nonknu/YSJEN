#pragma once

#ifdef  YE_PLATFORM_WINDOWS
	
extern	YSJEN::Application*  YSJEN::CreatApplication();

int main(int argc, char** argv) {

	auto app = YSJEN::CreatApplication();
	app->run();
	delete app;
}
#endif // 
