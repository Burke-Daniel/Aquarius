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

	m_texture = std::make_shared<Aquarius::Texture>("Assets/container.jpg");
	m_texture->bind();
	Aquarius::Renderer::Init();
	m_texture = std::make_shared<Aquarius::Texture>("Assets/container.jpg");
	m_texture->bind(0);
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t)
{
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();
	Aquarius::Renderer::SetProjection(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));
	Aquarius::Renderer::DrawQuad(
		{300, 200},
		{150, 150},
		45,
		{0, 0, 0 ,1}
	);
<<<<<<< HEAD
	m_texture->bind(0);
	Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());

=======

	m_texture->bind();

	Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());
>>>>>>> f69b753 (Modify Sandbox to render container image in rectangle)
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
