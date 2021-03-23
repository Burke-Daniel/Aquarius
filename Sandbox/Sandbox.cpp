#include "Sandbox.h"
#include "RPG/LevelEditorLayer.h"

#include "IntroLayer.h"
#include "BubbleSortLayer.h"
#include "ManagerLayer.h"
#include "PongLayer.h"

#include <glm/gtc/matrix_transform.hpp>


SandboxLayer::SandboxLayer()
    : Layer("Sandbox", true)
{}

void SandboxLayer::onCreation()
{
    Aquarius::Application* app = Aquarius::Application::get();
    Aquarius::Window* window = app->getWindow();

    int height = window->getHeight();
    int width = window->getWidth();

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::TextureConfiguration texConfig = {
        Aquarius::TextureWrapOption::Repeat,
        Aquarius::TextureWrapOption::Repeat,
        Aquarius::TextureFilteringOption::Linear,
        Aquarius::TextureFilteringOption::Linear
    };

    m_texture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/greenguy.png", texConfig, true);
    m_texture->bind(0);

    Aquarius::SpriteSheet sheet(m_texture.get(), 32, 32);
    m_uv = sheet.getSpriteCoords(0, 1);

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

    Aquarius::Renderer::DrawQuad(
        { 25, 400},
        { 50, 50},
        m_texture.get()
    );

    Aquarius::Renderer::DrawQuad(
        { 50, 200 },
        { 50, 50},
        m_texture.get()
    );

    Aquarius::Renderer::DrawQuad(
        { 200, 200 },
        { 50, 50 },
        m_texture.get(),
        &m_uv
    );

    Aquarius::Renderer::DrawQuad(
        { 200, 200 },
        { 50, 50},
        m_texture.get()
    );

    AQ_TRACE("Frametime: %v ms", ts);
    AQ_TRACE("FPS: %v", 1000 / ts);
}

Sandbox::Sandbox()
    : Aquarius::Application("Sandbox")
{
    Aquarius::Log::setLogLevel(Aquarius::LogLevel::Info);

    auto introLayer = PushLayer(std::make_unique<IntroLayer>());
    auto pongLayer = PushLayer(std::make_unique<PongLayer>());
    auto bubbleSortLayer = PushLayer(std::make_unique<BubbleSortLayer>());
    auto rpgLayer = PushLayer(std::make_unique<LevelEditorLayer>());

    PushLayer(std::make_unique<ManagerLayer>(
        std::vector<Aquarius::Layer*>{ introLayer, pongLayer, bubbleSortLayer, rpgLayer }));
    
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
    return std::make_unique<Sandbox>();
}
