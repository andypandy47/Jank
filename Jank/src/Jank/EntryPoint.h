#pragma once

#ifdef JANK_PLATFORM_WINDOWS

extern Jank::Application* Jank::CreateApplication();

int main(int argc, char** argv) {

	auto app = Jank::CreateApplication();
	app->Run();
	delete app;
}

#endif