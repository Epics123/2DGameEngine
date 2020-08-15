#include "mpch.h"
#include "Mayhem/Core/Input.h"

#include "Mayhem/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Mayhem
{
	bool Input::isKeyPressed(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<uint32_t>(key));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<uint32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::getMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float Input::getMouseX()
	{
		auto[x, y] = getMousePosition();

		return x;
	}

	float Input::getMouseY()
	{
		auto [x, y] = getMousePosition();

		return y;
	}
}