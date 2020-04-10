#pragma once

#include "Core.h"

namespace Jank{

	class JANK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}

