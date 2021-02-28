#include "Sandbox.h"

SandboxLayer::SandboxLayer(const std::string& vertexShader, const std::string& fragmentShader)
	: Layer("Sandbox"),
	m_ShaderProgram(std::make_shared<Aquarius::Shader>(vertexShader, fragmentShader))
{}

void SandboxLayer::onCreation()
{
	m_ShaderProgram->activate();

	m_vertexBuffer = std::make_shared<Aquarius::VertexBuffer>(
		m_triangleVertices.data(), m_triangleVertices.size() * sizeof(float));

	m_indexBuffer = std::make_shared<Aquarius::IndexBuffer>(m_indices.data(), m_indices.size());

	m_bufferLayout = std::make_shared<Aquarius::BufferLayout>(std::initializer_list<Aquarius::VertexElement>{
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 2, false),
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 3, false)
	});

	m_vertexArray = std::make_shared<Aquarius::VertexArray>(m_vertexBuffer, m_indexBuffer, *m_bufferLayout);
	m_vertexArray->activate();
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t)
{
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();
	Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());
}

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{
	PushLayer(std::make_unique<SandboxLayer>("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl"));
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
	return std::make_unique<Sandbox>();
}
