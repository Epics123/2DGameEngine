#include "mpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mayhem
{
	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}