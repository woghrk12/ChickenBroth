#include <ChickenBroth.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public ChickenBroth::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) 
	{
		// Flat Vertex Resources {x, y, z, x of the corner, y of the corner}
		float flatVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		// Flat Vertex Buffer
		ChickenBroth::Ref<ChickenBroth::VertexBuffer> flatVertexBuffer;
		flatVertexBuffer.reset(ChickenBroth::VertexBuffer::Create(flatVertices, sizeof(flatVertices)));
		flatVertexBuffer->SetLayout({
				{ ChickenBroth::ShaderDataType::Float3, "a_Position" },
				{ ChickenBroth::ShaderDataType::Float2, "a_TexCoord" }
			});

		// Flat Index Resources
		uint32_t flatIndices[6] = { 0, 1, 2, 2, 3, 0 };

		// Flat Index Buffer
		ChickenBroth::Ref<ChickenBroth::IndexBuffer> flatIndexBuffer;
		flatIndexBuffer.reset(ChickenBroth::IndexBuffer::Create(flatIndices, sizeof(flatIndices) / sizeof(uint32_t)));

		// Flat vertex array
		m_FlatVertexArray.reset(ChickenBroth::VertexArray::Create());
		m_FlatVertexArray->AddVertexBuffer(flatVertexBuffer);
		m_FlatVertexArray->SetIndexBuffer(flatIndexBuffer);

		// Flat Color Shader Resources
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		// Flat Color Shader
		m_FlatColorShader.reset(ChickenBroth::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		// Flat Texture Shader Resources
		std::string flatTextureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;
			
			void main()
			{
				v_TexCoord = a_TexCoord;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatTextureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		// Flat Texture Resources
		m_Texture = ChickenBroth::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = ChickenBroth::Texture2D::Create("assets/textures/ChernoLogo.png");

		// Flat Texture Shader
		m_FlatTextureShader.reset(ChickenBroth::Shader::Create(flatTextureShaderVertexSrc, flatTextureShaderFragmentSrc));

		std::dynamic_pointer_cast<ChickenBroth::OpenGLShader>(m_FlatTextureShader)->Bind();
		std::dynamic_pointer_cast<ChickenBroth::OpenGLShader>(m_FlatTextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(ChickenBroth::Timestep ts) override 
	{
		if (ChickenBroth::Input::IsKeyPressed(CB_KEY_LEFT)) m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ChickenBroth::Input::IsKeyPressed(CB_KEY_RIGHT)) m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (ChickenBroth::Input::IsKeyPressed(CB_KEY_UP)) m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ChickenBroth::Input::IsKeyPressed(CB_KEY_DOWN)) m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (ChickenBroth::Input::IsKeyPressed(CB_KEY_A)) m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (ChickenBroth::Input::IsKeyPressed(CB_KEY_D)) m_CameraRotation -= m_CameraRotationSpeed * ts;

		ChickenBroth::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ChickenBroth::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ChickenBroth::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ChickenBroth::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ChickenBroth::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_FlatColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				ChickenBroth::Renderer::Submit(m_FlatColorShader, m_FlatVertexArray, transform);
			}
		}
		
		m_Texture->Bind();
		ChickenBroth::Renderer::Submit(m_FlatTextureShader, m_FlatVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		ChickenBroth::Renderer::Submit(m_FlatTextureShader, m_FlatVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		ChickenBroth::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_FlatColor));
		ImGui::End();
	}

	void OnEvent(ChickenBroth::Event& event) override 
	{
		
	}

private:
	ChickenBroth::Ref<ChickenBroth::Shader> m_FlatColorShader, m_FlatTextureShader;
	ChickenBroth::Ref<ChickenBroth::VertexArray> m_FlatVertexArray;

	glm::vec3 m_FlatColor = glm::vec3(0.2f, 0.3f, 0.8f);

	ChickenBroth::Ref<ChickenBroth::Texture2D> m_Texture, m_LogoTexture;

	// Camera variables
	ChickenBroth::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public ChickenBroth::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer()); ;
	}

	~Sandbox() {}
};

ChickenBroth::Application* ChickenBroth::CreateApplication() { return new Sandbox(); }