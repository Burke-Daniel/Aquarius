#include "Sandbox.h"

#include <glm/gtc/matrix_transform.hpp>

SandboxLayer::SandboxLayer()
    : Layer("Sandbox")
{}

void SandboxLayer::onCreation()
{
    m_ShaderProgram = std::make_shared<Aquarius::Shader>("Sandbox/Shaders/modifiableVertexShader.glsl", 
                                                         "Sandbox/Shaders/modifiableFragmentShader.glsl");

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

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::Renderer::Init();

    m_texture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/container.jpg");
    m_texture->bind(0);
    Aquarius::Renderer::Init();
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t ts)
{
    m_Camera->onUpdate(ts);	
    glm::vec3 cameraPos = m_Camera->getPosition();

    Aquarius::Renderer::BeginScene(m_Camera.get());
    Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
    Aquarius::Renderer::Clear();

    // Draw quad in center and follow camera
    // In the future, camera should probably follow quad
    Aquarius::Renderer::DrawQuad(
        {cameraPos.x + 350, cameraPos.y + 250},
        {100, 100},
         0,
        {1, 0.5, 1, 1}
    );

    Aquarius::Renderer::DrawQuad(
        {100, 150},
        {100, 100},
         0,
        {1, 1, 1, 1}
    );

    /// Aquarius::Renderer::Submit(m_vertexArray.get(), m_ShaderProgram.get());
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
