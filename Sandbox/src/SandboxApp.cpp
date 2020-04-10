
#include <Jank.h>

class Sandbox : public Jank::Application {
public:
	Sandbox() {}
	~Sandbox() {}

};

Jank::Application* Jank::CreateApplication() {
	return new Sandbox();
}