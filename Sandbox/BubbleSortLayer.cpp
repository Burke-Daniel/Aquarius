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

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::Renderer::Init();
}

void BubbleSortLayer::onEvent(const Aquarius::Event& event)
{
    auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent&>(event);

    switch (keyPressEvent.getCode())
    {
        case(Aquarius::Input::KeyCode::Key_p):
        {
            isActive() ? deactivate() : activate();

            if(Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_r))
            {
                resetSort = true;
            }

            break;
        }

        case(Aquarius::Input::KeyCode::Key_up):
        {
            if(delay >= 0)
            {
                delay = delay - 200;
            }
            break;
        }

        case(Aquarius::Input::KeyCode::Key_down):
        {
            if(delay >= 0)
            {
                delay = delay + 200;
            }

            break;
        }

        case(Aquarius::Input::KeyCode::Key_r):
        {
            resetSort = true;
            break;
        }
    }
}

void BubbleSortLayer::onUpdate(Aquarius::timeDelta_t ts)
{
    if (resetSort)
    {
        for (int i = 0; i < 100; i++)
        {
            barHeights[i] = rand() % 750 + 30;
        }

        resetSort = false;
    }

    if (isActive())
    {
        Aquarius::Renderer::BeginScene(m_Camera.get());
        Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
        Aquarius::Renderer::Clear();

        renderBars(100);

        swapBars(i, j);
        i += 1;
        j += 1;

        if(i == 99 && j ==100)
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
        Aquarius::Renderer::DrawQuad(
                { position, 0} ,
                { barWidth, barHeights[i] },
                0,
                { barColors[0], barColors[1], barColors[2], barColors[3] }
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
