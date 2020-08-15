#pragma once

#include "Mayhem/Core/Core.h"
#include "Mayhem/Core/KeyCodes.h"
#include "Mayhem/Core/MouseButtonCodes.h"

namespace Mayhem
{

	class MAYHEM_API Input
	{
	public:
		static bool isKeyPressed(KeyCode key);
		static bool isMouseButtonPressed(MouseCode button);
		static std::pair<float, float> getMousePosition();
		static float getMouseX();
		static float getMouseY();
	};
}