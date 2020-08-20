#pragma once

#include "Mayhem/Core/Layer.h"

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

		virtual void onAttatch() override;
		virtual void onDetatch() override;
		virtual void onEvent(Event& e) override;

		void begin();
		void end();

		void blockEvents(bool block) { mBlockEvents = block; }

	private:
		bool mBlockEvents = true;
		float mTime = 0.0f;
	};
}