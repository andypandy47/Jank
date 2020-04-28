#pragma once

#include "Jank/Core.h"
#include "Jank/Events/Event.h"
#include "Jank/Events/ApplicationEvent.h"
#include "Jank/Window.h"
#include "Jank/Layerstack.h"
#include "Jank/ImGui/ImGuiLayer.h"

#include "Jank/Core/Timestep.h"

namespace Jank
{

	class JANK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_Layerstack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

