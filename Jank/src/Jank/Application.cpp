#include "Jankpch.h"
#include "Application.h"

#include "Jank/Events/ApplicationEvent.h"
#include "Jank/Log.h"

namespace Jank {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			JANK_TRACE(e);
		}

		while (true) {

		}
	}
}