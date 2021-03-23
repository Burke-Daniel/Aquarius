#include "BubbleSortLayer.h"

#include <chrono>
#include <thread>

BubbleSortLayer::BubbleSortLayer()
        : Aquarius::Layer("Bubble Sort", true)
        {
            app->getEventHandler().subscribe(Aquarius::eventType::KeyPressedEvent,
                                            [&](const Aquarius::Event& event)
                                            {
                                                onEvent(event);
                                            });
        }

void BubbleSortLayer::onCreation()
{
    int height = window->getHeight();
    int width = window->getWidth();

    m_Camera = std::make_unique<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::Renderer::Init();
}

void BubbleSortLayer::onEvent(const Aquarius::Event& event)
{
    auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent &>(event);

    switch (keyPressEvent.getCode()) {
        case (Aquarius::Input::KeyCode::Key_up): {
            if (delay >= 0) {
                delay = delay - 200;
            }
            break;
        }

        case (Aquarius::Input::KeyCode::Key_down): {
            if (delay >= 0) {
                delay = delay + 200;
            }

            break;
        }

        case (Aquarius::Input::KeyCode::Key_r): {
            resetSort = true;
            break;
        }
    }
}

void BubbleSortLayer::onUpdate(Aquarius::timeDelta_t ts)
{
    if (resetSort)
    {
        for (int i = 0; i < numRectangles; i++)
        {
            barHeights[i] = (rand() % (window->getHeight() - 100)) + 30;
        }

        resetSort = false;
    }

    if (isActive())
    {
        Aquarius::Renderer::ClearColor({ 219.0 / 255.0, 219.0 / 255.0, 219.0 / 255.0 });
        Aquarius::Renderer::Clear();

        renderBars(numRectangles);

        swapBars(i, j);
        i += 1;
        j += 1;

        if(i == numRectangles - 1 && j == numRectangles)
            {
                i = 0;
                j = 1;
            }

        // This delay will allow for the changes occurring during the sort to be visible
        std::this_thread::sleep_for(std::chrono::microseconds(delay));
    }
}

void BubbleSortLayer::renderBars(int size)
{
    int position = 0;

    for(int i = 0; i < size; i++)
    {
        auto normalizationConst = barHeights[i] / (float)(window->getHeight() - 70);
        Aquarius::Renderer::DrawQuad(
                { position, window->getHeight() - barHeights[i]} ,
                { barWidth, barHeights[i] },
                0,
                { 1 - barColors.x * normalizationConst, 0, 0, barColors.w }
        );

        position += barWidth + 1;
    }
}

void BubbleSortLayer::swapBars(int i, int j)
{
    if(barHeights[i] > barHeights[j])
    {
        std::swap(barHeights[i], barHeights[j]);
    }
}
