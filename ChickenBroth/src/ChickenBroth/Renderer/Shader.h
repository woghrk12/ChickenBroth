#pragma once

#include "cbpch.h"

#include <string>
#include <glm/glm.hpp>

namespace ChickenBroth
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		unsigned int m_RendererID;
	};
}