#include "cbpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ChickenBroth
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}