#pragma once

#include <Aquarius.h>

class BubbleSortLayer : public Aquarius::Layer
{
public:
    BubbleSortLayer();

    void onCreation() override;
    void onUpdate(Aquarius::timeDelta_t time) override;

private:
    int i = 0;
    int j = 1;
    int barHeights [100];
    void renderBars(int size);
    void swapBars(int i, int j);
    Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
};
