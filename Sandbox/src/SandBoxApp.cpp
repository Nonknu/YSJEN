#include"YSJEN.h"

class SandBox : public YSJEN::Application {
public:
	SandBox() {
	
	}

	~SandBox() {
	
	}
};

YSJEN::Application* YSJEN::CreatApplication() {
	return new SandBox();
}