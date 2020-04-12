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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


