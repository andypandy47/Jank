#pragma once

#include "Jank/Core.h"
#include "Jank/Events/Event.h"
#include "Jank/Events/ApplicationEvent.h"
#include "Jank/Window.h"
#include "Jank/Layerstack.h"

namespace Jank{

	class JANK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_Layerstack;
	};

	//To be defined in client
	Application* CreateApplication();
}

