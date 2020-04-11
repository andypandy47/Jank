
#include <Jank.h>

class ExampleLayer : public Jank::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override {
		
	}

	void OnEvent(Jank::Event& e) {
		
	}
};

class Sandbox : public Jank::Application {
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer()); 
		PushOverlay(new Jank::ImGuiLayer());
	}
	~Sandbox() {}

};

Jank::Application* Jank::CreateApplication() {
	return new Sandbox();
}