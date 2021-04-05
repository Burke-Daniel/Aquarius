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
    Aquarius::Application* app = Aquarius::Application::get();
    Aquarius::Window* window = app->getWindow();

    static constexpr int numRectangles = 40;
    bool pauseSort = false;
    bool resetSort = true;
    float barWidth = (window->getWidth() / numRectangles) - 1.0;
    glm::vec4 barColors = {1.0, 1.0, 1.0, 1.0};
    int barHeights [numRectangles];
    int delayConstant = 750;
    int i = 0;
    int j = 1;
    void renderBars(int size);
    void swapBars(int i, int j);

    Aquarius::uniquePtr<Aquarius::OrthographicCamera> m_Camera;
};
