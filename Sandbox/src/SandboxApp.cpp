#include <Jank.h>

#include <Platform\OpenGl\OpenGLShader.h>

#include "ImGui/imgui.h"

#include <glm\glm\ext\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

class ExampleLayer : public Jank::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPosition(0.0f)
	{
		m_VertexArray.reset(Jank::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f
		};

		Jank::Ref<Jank::VertexBuffer> vb;
		vb.reset(Jank::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jank::BufferLayout layout = {
				{Jank::ShaderDataType::Float3, "a_Position"},
				{Jank::ShaderDataType::Float4, "a_Color" }
		};

		vb->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vb);

		uint32_t indices[3] = { 0 ,1 ,2 };
		Jank::Ref<Jank::IndexBuffer> ib;
		ib.reset(Jank::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(ib);

		m_SquareVA.reset(Jank::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Jank::Ref<Jank::VertexBuffer> squareVB;
		squareVB.reset(Jank::VertexBuffer::Create(squareVertices, sizeof(vertices)));
		squareVB->SetLayout({
				{Jank::ShaderDataType::Float3, "a_Position"},
				{Jank::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0 ,1 ,2, 2, 3, 0 };
		Jank::Ref<Jank::IndexBuffer> squareIB;
		squareIB.reset(Jank::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_flatColourShader = Jank::Shader::Create("assets/shaders/FlatColour.glsl");

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Jank::Texture2D::Create("assets/textures/Checkerboard.png");
		
		m_LogoTexture = Jank::Texture2D::Create("assets/textures/test.png");

		std::dynamic_pointer_cast<Jank::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Jank::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Jank::Timestep ts) override 
	{
		float deltaTime = ts;

		if (Jank::Input::IsKeyPressed(JANK_KEY_LEFT))
			m_CamPosition.x -= m_CameraMoveSpeed * deltaTime;
		else if (Jank::Input::IsKeyPressed(JANK_KEY_RIGHT))
			m_CamPosition.x += m_CameraMoveSpeed * deltaTime;

		if (Jank::Input::IsKeyPressed(JANK_KEY_UP))
			m_CamPosition.y += m_CameraMoveSpeed * deltaTime;
		else if (Jank::Input::IsKeyPressed(JANK_KEY_DOWN))
			m_CamPosition.y -= m_CameraMoveSpeed * deltaTime;

		if (Jank::Input::IsKeyPressed(JANK_KEY_A))
			m_CamRotation -= m_CameraRotationSpeed * deltaTime;
		else if (Jank::Input::IsKeyPressed(JANK_KEY_D))
			m_CamRotation += m_CameraRotationSpeed * deltaTime;


		Jank::RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Jank::RenderCommand::Clear();

		m_Camera.SetPosition(m_CamPosition);
		m_Camera.SetRotation(m_CamRotation);

		Jank::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//std::dynamic_pointer_cast<Jank::OpenGLShader>(m_flatColourShader)->Bind();
		m_flatColourShader->Bind();
		std::dynamic_pointer_cast<Jank::OpenGLShader>(m_flatColourShader)->UploadUniformFloat3("u_Colour", m_SquareColour);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Jank::Renderer::Submit(m_flatColourShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		textureShader->Bind();
		std::dynamic_pointer_cast<Jank::OpenGLShader>(textureShader)->UploadUniformFloat4("u_Colour", m_TextureColour);

		m_Texture->Bind();
		Jank::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		Jank::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Jank::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));
		ImGui::ColorEdit4("Texture Colour", glm::value_ptr(m_TextureColour));
		ImGui::End();
	}

	void OnEvent(Jank::Event& e) 
	{
	}


private:
	Jank::ShaderLibrary m_ShaderLibrary;

	Jank::Ref<Jank::VertexArray> m_VertexArray;

	Jank::Ref<Jank::VertexArray> m_SquareVA;
	Jank::Ref<Jank::Shader> m_flatColourShader;

	Jank::Ref<Jank::Texture2D> m_Texture, m_LogoTexture;

	Jank::OrthographicCamera m_Camera;

	glm::vec3 m_CamPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CamRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColour = { 0.2f, 0.8f, 0.3f };
	glm::vec4 m_TextureColour = { 1.0, 1.0, 1.0, 1.0 };
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