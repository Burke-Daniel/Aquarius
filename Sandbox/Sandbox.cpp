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
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 3, false),
		Aquarius::VertexElement(Aquarius::ShaderType::Float, 2, false)
	});

	m_vertexArray = std::make_shared<Aquarius::VertexArray>(m_vertexBuffer, m_indexBuffer, *m_bufferLayout);
	m_vertexArray->activate();

	m_texture = std::make_shared<Aquarius::Texture>("Assets/container.jpg");
	m_texture->bind(GL_TEXTURE0);
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t)
{
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();

	m_texture->bind(GL_TEXTURE0);

	Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());
}

Sandbox::Sandbox()
	: Aquarius::Application("Sandbox")
{
	PushLayer(std::make_unique<SandboxLayer>("Shaders/modifiableVertexShader.glsl", "Shaders/modifiableFragmentShader.glsl"));
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
	return std::make_unique<Sandbox>();
}
