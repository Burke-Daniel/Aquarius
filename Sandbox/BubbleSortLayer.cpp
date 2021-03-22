#include "BubbleSortLayer.h"

#include <chrono>
#include <thread>

BubbleSortLayer::BubbleSortLayer()
        : Aquarius::Layer("Bubble Sort")
        {
            app->getEventHandler().subscribe(Aquarius::eventType::MouseScrolledEvent,
                                            [&](const Aquarius::Event& event)
                                            {
                                                onEvent(event);
                                            });
        }

void BubbleSortLayer::onCreation()
{
    //Aquarius::Application* app = Aquarius::Application::get();
    //Aquarius::Window* window = app->getWindow();

    int height = window->getHeight();
    int width = window->getWidth();

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::Renderer::Init();

    // Populate the bar heights with random values
    for (int i = 0; i < 100; i++)
    {
        barHeights[i] = rand() % 750 + 30;
    }
}

void BubbleSortLayer::onEvent(const Aquarius::Event& event)
{
    auto mouseScrolledEvent = static_cast<const Aquarius::MouseScrolledEvent&>(event);

    delay = mouseScrolledEvent.getXOffset();
}

void BubbleSortLayer::onUpdate(Aquarius::timeDelta_t ts)
{

    Aquarius::Application* app = Aquarius::Application::get();
    Aquarius::Window* window = app->getWindow();

    m_Camera->onUpdate(ts);

    Aquarius::Renderer::BeginScene(m_Camera.get());
    Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
    Aquarius::Renderer::Clear();


    renderBars(100);

    swapBars(i, j);
    i = i+1;
    j = j+1;

    if(i == 99 and j ==100)
    {
        i = 0;
        j = 1;
    }

    // This delay will allow for the changes occurring during the sort to be visible
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

void BubbleSortLayer::renderBars(int size)
{
    int position = 0;

    for(int i = 0; i < size; i++)
    {
        Aquarius::Renderer::DrawQuad(
                {position, 0},
                {10, barHeights[i]},
                0,
                {barColors[0],barColors[1],barColors[2],barColors[3]}
        );

        position = position + 11;
    }
}

void BubbleSortLayer::swapBars(int i, int j)
{
    if(barHeights[i] > barHeights[j])
    {
        int holder = barHeights[i];
        barHeights[i] = barHeights[j];
        barHeights[j] = holder;
    }
}
