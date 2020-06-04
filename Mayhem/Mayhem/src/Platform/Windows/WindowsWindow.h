#pragma once

#include "Mayhem/Window.h"
#include "Mayhem/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Mayhem
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return mData.Width; }
		inline unsigned int getHeight() const override { return mData.Height; }

		//Window Attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
		void setVsync(bool enabled) override;
		bool isVsync() const override;

		inline virtual void* getNativeWindow() const { return mWindow; }

	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* mWindow;
		GraphicsContext* mContext;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData mData;
	};
}