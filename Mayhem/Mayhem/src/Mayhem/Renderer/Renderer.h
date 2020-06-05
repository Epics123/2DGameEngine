#pragma once


namespace Mayhem
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return sRendererAPI; }

	private:
		static RendererAPI sRendererAPI;
	};
}