#pragma once

#ifdef JANK_PLATFORM_WINDOWS

extern Jank::Application* Jank::CreateApplication();

int main(int argc, char** argv) 
{
	Jank::Log::Init();
	JANK_CORE_WARN("Initialised Log!");
	int a = 5;
	JANK_INFO("Hello! Var={0}", a);

	auto app = Jank::CreateApplication();
	app->Run();
	delete app;
}

#endif