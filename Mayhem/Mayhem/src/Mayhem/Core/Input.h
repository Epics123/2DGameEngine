#pragma once

#include "Mayhem/Core/KeyCodes.h"
#include "Mayhem/Core/MouseButtonCodes.h"

#include <glm/glm.hpp>

namespace Mayhem
{
	class Input
	{
	public:
		static bool isKeyPressed(KeyCode key);
		static bool isMouseButtonPressed(MouseCode button);
		static glm::vec2 getMousePosition();
		static float getMouseX();
		static float getMouseY();
	};
}