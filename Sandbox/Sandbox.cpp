#include "Sandbox.h"

#include <glm/gtc/matrix_transform.hpp>

SandboxLayer::SandboxLayer()
	: Layer("Sandbox")
{}

void SandboxLayer::onCreation()
{
	m_vertexBuffer = std::make_shared<Aquarius::VertexBuffer>(
		m_triangleVertices.data(), m_triangleVertices.size() * sizeof(float));

	m_indexBuffer = std::make_shared<Aquarius::IndexBuffer>(m_indices.data(), m_indices.size());

	m_bufferLayout = std::make_shared<Aquarius::BufferLayout>(std::initializer_list<Aquarius::VertexElement>{
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 2, false),
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 3, false),
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 2, false)
	});

	m_vertexArray = std::make_shared<Aquarius::VertexArray>(m_vertexBuffer, m_indexBuffer, *m_bufferLayout);
	m_vertexArray->activate();

	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	int height = window->getHeight();
	int width = window->getWidth();

	// TODO: Create camera and start scene with it
	m_Camera = std::make_shared<Aquarius::OrthographicCamera>(0.1, 0, width, height, 0);
	Aquarius::Renderer::Init();

	m_texture = std::make_shared<Aquarius::Texture>("Assets/container.jpg");
	m_texture->bind();
	Aquarius::Renderer::Init();
	m_texture->bind(0);
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t ts)
{
	m_Camera->onUpdate(ts);
	glm::vec3 cameraPos = m_Camera->getPosition();
	m_quadPosition = glm::vec2(cameraPos.x, cameraPos.y);
	AQ_INFO("\ncamera X: %v\n camera Y: %v", cameraPos.x, cameraPos.y);

	Aquarius::Renderer::BeginScene(m_Camera.get());
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();

	//Aquarius::Renderer::DrawQuad(
	//	m_quadPosition,
	//	{ 150, 150 },
	//	0,
	//	{ 0, 1, 1 ,1 }
	//);

	Aquarius::Renderer::DrawQuad(
		{400-5, 300-5},
		{10, 10},
		0,
		{ 1, 0.5, 1 ,1 }
	);

	m_texture->bind(0);

	Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());
}

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{
	PushLayer(std::make_unique<SandboxLayer>());
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
	return std::make_unique<Sandbox>();
}
