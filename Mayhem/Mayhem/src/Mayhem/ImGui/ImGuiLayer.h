#pragma once

#include "Mayhem/Layer.h"

#include "Mayhem/Events/KeyEvent.h"
#include "Mayhem/Events/MouseEvent.h"
#include "Mayhem/Events/ApplicationEvent.h"

namespace Mayhem
{
	class MAYHEM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttatch();
		void onDetatch();
		void onUpdate();
		void onEvent(Event& event);

	private:
		//TODO: add copy and paste

		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseMoveEvent(MouseMoveEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);

	private:
		float mTime = 0.0f;
	};
}