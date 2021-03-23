#include "IntroLayer.h"

#include "Aquarius.h"

#include <thread>
#include <chrono>


IntroLayer::IntroLayer()
        : Layer("Intro", true)
{}

void IntroLayer::onCreation()
{
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

    MUNLogo = std::make_shared<Aquarius::Texture>("Resources/mun-logo.png", texConfig, true);

    Aquarius::Renderer::Init();
}

void IntroLayer::onUpdate(Aquarius::timeDelta_t dt)
{
    int height = window.getHeight();
    int width = window.getWidth();

    Aquarius::Renderer::BeginScene(m_Camera.get());
    Aquarius::Renderer::ClearColor({ 1, 1, 1});
    Aquarius::Renderer::Clear();

    if(drawAquarius)
    {
        // Draw up
        if(alpha <= 1 and !maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    {200, 100},
                    {400, 300},
                    AquariusLogo.get(),
                    nullptr,
                    0,
                    {1,1,1,alpha}
            );

            if(alpha == 1)
            {
                maxAlpha = true;
            }

            else
            {
                alpha = alpha + 0.01;
            }
        }

        // Draw back down
        else if (alpha >= 0 and maxAlpha)
        {
            Aquarius::Renderer::DrawQuad(
                    {200, 100},
                    {400, 300},
                    AquariusLogo.get(),
                    nullptr,
                    0,
                    {1,1,1,alpha}
            );

            if(alpha == 0)
            {
                alpha = 0;
                drawAquarius = false;
                drawMUN = true;
            }

            else
            {
                alpha = alpha - 0.01;
            }
        }

        else
        {
            alpha = 0;
            drawAquarius = false;
            drawMUN = true;
        }
    }

    if(drawMUN)
    {
        Aquarius::Renderer::DrawQuad(
                {200, 100},
                {400, 300},
                MUNLogo.get(),
                nullptr,
                0,
                {1,1,1,0.5}
        );
    }

    //std::this_thread::sleep_for(std::chrono::microseconds (1000));
}