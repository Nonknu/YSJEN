#pragma once

#include "Core.h"

namespace YSJEN {
	class YSJEN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	//to be define in client
	Application* CreatApplication();
}


