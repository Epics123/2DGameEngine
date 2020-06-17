#include "mpch.h"
#include "WindowsInput.h"

#include "Mayhem/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Mayhem
{
	Input* Input::sInstance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::getMouseXImpl()
	{
		auto[x, y] = getMousePositionImpl();

		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePositionImpl();

		return y;
	}
}