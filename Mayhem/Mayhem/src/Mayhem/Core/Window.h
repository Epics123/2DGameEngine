#pragma once

#include "mpch.h"

#include "Core.h"
#include "Mayhem/Events/Event.h"

namespace Mayhem
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Mayhem Engine", unsigned int width = 1280, unsigned int height = 720)
			:Title(title), Width(width), Height(height){}
	};

	//Interface representing a desktop system based Window
	class MAYHEM_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		//Window Attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVsync(bool enabled) = 0;
		virtual bool isVsync() const = 0;

		virtual void* getNativeWindow() const = 0; //Void pointer can hold address of any type and can be typcasted to any type.

		static Window* createWindow(const WindowProps& props = WindowProps());
	};
}