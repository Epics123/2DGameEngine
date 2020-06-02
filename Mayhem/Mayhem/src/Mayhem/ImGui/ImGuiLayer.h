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

		virtual void onAttatch() override;
		virtual void onDetatch() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float mTime = 0.0f;
	};
}