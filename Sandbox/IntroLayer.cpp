#include "IntroLayer.h"

#include "Aquarius.h"


IntroLayer::IntroLayer()
        : Layer("Intro", true)
{
    app.getEventHandler().subscribe(Aquarius::eventType::WindowResizedEvent,
                                    [&](const Aquarius::Event& event)
    {
        onEvent(event);
    });
}

void IntroLayer::onCreation()
{
    xPosition = window.getWidth()/2;
    yPosition = window.getHeight()/2;
    int height = window.getHeight();
    int width = window.getWidth();

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::TextureConfiguration texConfig = {
            Aquarius::TextureWrapOption::Repeat,
            Aquarius::TextureWrapOption::Repeat,
            Aquarius::TextureFilteringOption::Linear,
            Aquarius::TextureFilteringOption::Linear
    };

    AquariusLogo = std::make_shared<Aquarius::Texture>("Resources/logo-black-transparent.png", texConfig, true);
    AquariusLogo->bind(0);

    MUNLogo = std::make_shared<Aquarius::Texture>("Sandbox/Assets/mun-logo.png", texConfig, true);
    MUNLogo->bind(0);

    Aquarius::Renderer::Init();
}

void IntroLayer::onEvent(const Aquarius::Event& event)
{
    auto windowResize = static_cast<const Aquarius::WindowResizedEvent&>(event);
    xPosition = windowResize.getWidth()/2;
    yPosition = windowResize.getHeight()/2;
}

void IntroLayer::onUpdate(Aquarius::timeDelta_t dt)
{
    float delay = dt * 0.5;

    Aquarius::Renderer::BeginScene(m_Camera.get());
    Aquarius::Renderer::ClearColor({ 1, 1, 1 });
    Aquarius::Renderer::Clear();

    if (drawAquarius)
    {
        // Fade the Aquarius logo on the window
        if (!maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    { xPosition-200, yPosition-150 },
                    { 400, 300 },
                    AquariusLogo.get(),
                    nullptr,
                    0,
                    { 1, 1, 1, alpha }
            );

            if (alpha < 1)
            {
                alpha = alpha + 0.001*delay;
            }

            else
            {
                maxAlpha = true;
            }
        }

        // Fade the Aquarius logo off the window
        else if (maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    { xPosition-200, yPosition-150},
                    { 400, 300},
                    AquariusLogo.get(),
                    nullptr,
                    0,
                    { 1, 1, 1, alpha}
            );

            if (alpha > 0)
            {
                alpha = alpha - 0.001 * delay;
            }

            else
            {
                alpha = 0;
                drawAquarius = false;
                drawMUN = true;
                maxAlpha = false;
            }
        }
    }

    if (drawMUN)
    {
        // Fade the MUN logo on the window
        if (!maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    { xPosition - 200,  yPosition - 150 },
                    { 400,  300 },
                    MUNLogo.get(),
                    nullptr,
                    0,
                    { 1, 1, 1, alpha }
            );

            if (alpha < 1.0)
            {
                alpha = alpha + 0.001 * delay;
            }

            else
            {
                maxAlpha = true;
            }
        }

        // Fade the MUN logo off the window
        else if (maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    { xPosition - 200, yPosition - 150 },
                    { 400, 300 },
                    MUNLogo.get(),
                    nullptr,
                    0,
                    { 1, 1,  1, alpha }
            );

            if (alpha > 0)
            {
                alpha = alpha - 0.001 * delay;
            }

            else
            {
                alpha = 0;
                drawMUN = false;
                maxAlpha = false;
                drawAquarius = true;
            }
        }
    }
}
