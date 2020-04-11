#pragma once

#include "Jank/Layer.h"
#include "Jank/Events/Event.h"
#include "Jank/Events/ApplicationEvent.h"
#include "Jank/Events/MouseEvent.h"
#include "Jank/Events/KeyEvent.h"

namespace Jank {
	
	class JANK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);

		static const char* GetClipboardText(void* user_data);
		static void SetClipboardText(void* user_data, const char* text);
	private:
		float m_Time = 0.0f;
	};
}


