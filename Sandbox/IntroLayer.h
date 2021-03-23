#pragma once

#include "Aquarius.h"


class IntroLayer : public Aquarius::Layer
{
public:
    IntroLayer();

    void onCreation() override;
    void onUpdate(Aquarius::timeDelta_t) override;

private:
    float alpha = 0.0;
    bool maxAlpha = false;
    bool drawAquarius = true;
    bool drawMUN = false;
    Aquarius::Application& app = *Aquarius::Application::get();
    Aquarius::Window& window = *app.getWindow();
    Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
    Aquarius::sharedPtr<Aquarius::Texture> AquariusLogo;
    Aquarius::sharedPtr<Aquarius::Texture> MUNLogo;
};