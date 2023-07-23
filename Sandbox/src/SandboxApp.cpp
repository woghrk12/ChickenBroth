#include <ChickenBroth.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public ChickenBroth::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) 
	{
		// Triangle Shader
		std::string triangleShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string triangleShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_TriangleShader.reset(ChickenBroth::Shader::Create(triangleShaderVertexSrc, triangleShaderFragmentSrc));

		// Triangle Vertex Array
		m_TriangleVA.reset(ChickenBroth::VertexArray::Create());

		// Triangle Vertex Buffer
		float triangleVertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<ChickenBroth::VertexBuffer> triangleVB;
		triangleVB.reset(ChickenBroth::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		triangleVB->SetLayout({ 
				{ ChickenBroth::ShaderDataType::Float3, "a_Position" },
				{ ChickenBroth::ShaderDataType::Float4, "a_Color" } 
			});

		m_TriangleVA->AddVertexBuffer(triangleVB);

		// Triangle Index Buffer
		uint32_t triangleIndices[3] = { 0, 1, 2 };

		std::shared_ptr<ChickenBroth::IndexBuffer> triangleIB;
		triangleIB.reset(ChickenBroth::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

		m_TriangleVA->SetIndexBuffer(triangleIB);


		// Square Shader
		std::string squareShaderVertexSrc = R"(
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

		std::string squareShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_SquareShader.reset(ChickenBroth::Shader::Create(squareShaderVertexSrc, squareShaderFragmentSrc));

		// Square Vertex Array
		m_SquareVA.reset(ChickenBroth::VertexArray::Create());

		// Square Vertex Buffer
		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f, 
			-0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<ChickenBroth::VertexBuffer> squareVB;
		squareVB.reset(ChickenBroth::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
				{ ChickenBroth::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		// Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<ChickenBroth::IndexBuffer> squareIB;
		squareIB.reset(ChickenBroth::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);
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

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				ChickenBroth::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}

		ChickenBroth::Renderer::Submit(m_TriangleShader, m_TriangleVA);

		ChickenBroth::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(ChickenBroth::Event& event) override 
	{
		
	}

private:
	std::shared_ptr<ChickenBroth::Shader> m_TriangleShader;
	std::shared_ptr<ChickenBroth::VertexArray> m_TriangleVA;

	std::shared_ptr<ChickenBroth::Shader> m_SquareShader;
	std::shared_ptr<ChickenBroth::VertexArray> m_SquareVA;

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