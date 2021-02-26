#include "Sandbox.h"

SandboxLayer::SandboxLayer(const std::string& vertexShader, const std::string& fragmentShader)
	: Aquarius::Layer("Sandbox"),
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

void SandboxLayer::onEvent(Aquarius::Event& event) {}

void SandboxLayer::updateAndRender(Aquarius::timeDelta_t time)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void SandboxLayer::onDestruction(){}

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{
	PushLayer(std::make_unique<SandboxLayer>("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl"));
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
	return std::make_unique<Sandbox>();
}
