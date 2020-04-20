#include <Jank.h>
#include "ImGui/imgui.h"

class ExampleLayer : public Jank::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6, 1.6, -0.9, 0.9f), m_CamPosition({0.0f, 0.0f, 0.0f})
	{
		m_VertexArray.reset(Jank::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Jank::VertexBuffer> vb;
		vb.reset(Jank::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jank::BufferLayout layout = {
				{Jank::ShaderDataType::Float3, "a_Position"},
				{Jank::ShaderDataType::Float4, "a_Color" }
		};

		vb->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vb);

		uint32_t indices[3] = { 0 ,1 ,2 };
		std::shared_ptr<Jank::IndexBuffer> ib;
		ib.reset(Jank::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(ib);

		m_SquareVA.reset(Jank::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Jank::VertexBuffer> squareVB;
		squareVB.reset(Jank::VertexBuffer::Create(squareVertices, sizeof(vertices)));
		squareVB->SetLayout({
				{Jank::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0 ,1 ,2, 2, 3, 0 };
		std::shared_ptr<Jank::IndexBuffer> squareIB;
		squareIB.reset(Jank::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Colour;
			
			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			in vec4 v_Colour;
			
			void main()
			{
				colour = v_Colour;
			}
		)";

		m_Shader.reset(new Jank::Shader(vertexSrc, fragmentSrc));

		std::string blueVertShader = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Colour;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragShader = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 v_Position;
			
			void main()
			{
				colour = vec4(0.3, 0.5, 0.3, 1.0);
			}
		)";

		m_BlueShader.reset(new Jank::Shader(blueVertShader, blueFragShader));
	}

	void OnUpdate() override 
	{
		if (Jank::Input::IsKeyPressed(JANK_KEY_LEFT))
			m_CamPosition.x -= m_CameraMoveSpeed;

		if (Jank::Input::IsKeyPressed(JANK_KEY_RIGHT))
			m_CamPosition.x += m_CameraMoveSpeed;

		if (Jank::Input::IsKeyPressed(JANK_KEY_UP))
			m_CamPosition.y += m_CameraMoveSpeed;

		if (Jank::Input::IsKeyPressed(JANK_KEY_DOWN))
			m_CamPosition.y -= m_CameraMoveSpeed;

		if (Jank::Input::IsKeyPressed(JANK_KEY_A))
			m_CamRotation -= m_CameraRotationSpeed;

		if (Jank::Input::IsKeyPressed(JANK_KEY_D))
			m_CamRotation += m_CameraRotationSpeed;


		Jank::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Jank::RenderCommand::Clear();

		m_Camera.SetPosition(m_CamPosition);
		m_Camera.SetRotation(m_CamRotation);

		Jank::Renderer::BeginScene(m_Camera);

		Jank::Renderer::Submit(m_BlueShader, m_SquareVA);
		Jank::Renderer::Submit(m_Shader, m_VertexArray);

		Jank::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Jank::Event& e) 
	{
	}


private:
	std::shared_ptr<Jank::Shader> m_Shader;
	std::shared_ptr<Jank::VertexArray> m_VertexArray;

	std::shared_ptr<Jank::VertexArray> m_SquareVA;
	std::shared_ptr<Jank::Shader> m_BlueShader;

	Jank::OrthographicCamera m_Camera;

	glm::vec3 m_CamPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CamRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
};

class Sandbox : public Jank::Application 
{
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer()); 
	}
	~Sandbox() {}

};

Jank::Application* Jank::CreateApplication() 
{
	return new Sandbox();
}