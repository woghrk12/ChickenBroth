#include "cbpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ChickenBroth
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			CB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
				
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);

		default:
			CB_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			CB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);

		default:
			CB_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

}