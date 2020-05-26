#pragma once

#include "Mayhem/Layer.h"

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
		float mTime = 0.0f;
	};
}