#pragma once

#include <Aquarius.h>

class BubbleSortLayer : public Aquarius::Layer
{
public:
    BubbleSortLayer();

    void onCreation() override;
    void onEvent(const Aquarius::Event&) override;
    void onUpdate(Aquarius::timeDelta_t time) override;

private:
    bool resetSort = true;
    bool isSafe = true;
    int barWidth = 10;
    int barColors [4] = {1, 1, 1, 1};
    int barHeights [100];
    int delay = 500;
    int i = 0;
    int j = 1;
    void renderBars(int size);
    void swapBars(int i, int j);

    Aquarius::Application* app = Aquarius::Application::get();
    Aquarius::Window* window = app->getWindow();

    Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
};
