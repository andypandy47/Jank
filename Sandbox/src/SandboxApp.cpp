#include <Jank.h>
#include "ImGui/imgui.h"

class ExampleLayer : public Jank::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override 
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello imgui!");
		ImGui::End();
	}

	void OnEvent(Jank::Event& e) 
	{
		
	}
};

class Sandbox : public Jank::Application 
{
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer()); 
	}
	~Sandbox() {}

};

Jank::Application* Jank::CreateApplication() 
{
	return new Sandbox();
}