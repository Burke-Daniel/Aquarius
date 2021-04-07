#include "BubbleSortLayer.h"

#include <chrono>
#include <thread>


BubbleSortLayer::BubbleSortLayer()
        : Aquarius::Layer("Bubble Sort", true)
        {
            app->getEventHandler().subscribe(Aquarius::eventType::KeyPressedEvent,
                                            [&](const Aquarius::Event& event)
                                            {
                                                onKeyEvent(event);
                                            });
            app->getEventHandler().subscribe(Aquarius::eventType::WindowResizedEvent,
                                             [&](const Aquarius::Event& event)
                                             {
                                                onResizeEvent(event);
                                             });
        }

void BubbleSortLayer::onCreation()
{
    int height = window->getHeight();
    int width = window->getWidth();

    m_Camera = std::make_unique<Aquarius::OrthographicCamera>(1, 0.01, height, width);
    m_FontTexture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/8bitfont.png", Aquarius::TextureConfiguration{}, true);
    m_Font = std::make_shared<Aquarius::Bitmap>(m_FontTexture.get(), 21, 28);

    Aquarius::Renderer::Init();
}

void BubbleSortLayer::onKeyEvent(const Aquarius::Event& event)
{
    auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent &>(event);

    switch (keyPressEvent.getCode())
    {
        case(Aquarius::Input::KeyCode::Key_r):
        {
            resetSort = true;
            break;
        }

        case(Aquarius::Input::KeyCode::Key_p):
        {
            if (!pauseSort)
            {
                pauseSort = true;
            }
            else
            {
                pauseSort = false;
            }
            break;
        }
    }
}

void BubbleSortLayer::onResizeEvent(const Aquarius::Event& event)
{
    auto windowResize = static_cast<const Aquarius::WindowResizedEvent&>(event);

    m_Height = window->getHeight();
    for (int i = 0; i < numRectangles; i++)
    {
        int heightFactor = m_Height*0.00005;
        barHeights[i] = barHeights[i]+(m_Height-30)*0.00005;
    }
}

void BubbleSortLayer::onUpdate(Aquarius::timeDelta_t dt)
{
    Aquarius::Renderer::Clear();

    int delay = dt * delayConstant;

    char comparisonCountDigits[4];

    sprintf(comparisonCountDigits, "%04d", comparisonCount);

    glm::vec2 titlePosition = { 10.0, 10.0 };
    glm::vec2 comparisonPosition = {10.0, 45.0};
    glm::vec2 statusPosition = {10.0, 65};

    m_Font->RenderText("BUBBLE SORT", titlePosition, 1.0, titleColor);
    m_Font->RenderText("COMPARISON COUNT-" + std::string(comparisonCountDigits), comparisonPosition, 0.5, titleColor);

    /*if (resized)
    {
        for (int i = 0; i < numRectangles; i++)
        {
            barHeights[i] += (m_Height-200)*0.00005;
        }

        AQ_CORE_INFO("Resized event");
        resized = false;
    }*/
    if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_m))
    {
        m_MenuOpen = true;
    }

    if (resetSort)
    {
        for (int i = 0; i < numRectangles; i++)
        {
            barHeights[i] = (rand() % (m_Height - 100)) + 30;
        }
        comparisonCount = 0;
        resetSort = false;
        m_Font->RenderText("SORT RESET", statusPosition, 0.5, titleColor);
    }

    if (pauseSort)
    {
        renderBars(numRectangles);
        m_Font->RenderText("SORT PAUSED", statusPosition, 0.5, { 1.0, 0.0, 0.0, 1.0 });
    }

    if (sorted)
    {
        renderBars(numRectangles);
    }

    if (!pauseSort)
    {
        Aquarius::Renderer::ClearColor({ 219.0 / 255.0, 219.0 / 255.0, 219.0 / 255.0 });
        renderBars(numRectangles);

        swapBars(i, j);
        i += 1;
        j += 1;

        if (i == numRectangles - 1 && j == numRectangles)
        {
                i = 0;
                j = 1;
        }

        comparisonCount++;

        if (std::is_sorted(barHeights, barHeights+40))
        {
            sorted = true;
            comparisonCount--;
            m_Font->RenderText("SORT COMPLETED", statusPosition, 0.5, { 0.133, 0.289, 0.010, 1.0 });
        }

        if (!(std::is_sorted(barHeights, barHeights+40)))
        {
            sorted = false;
            m_Font->RenderText("SORT IN PROGRESS", statusPosition, 0.5, { 0.0, 0.0, 1.0, 1.0 });
        }

        // This delay will allow for the changes occurring during the sort to be visible
        std::this_thread::sleep_for(std::chrono::microseconds(delay));
    }
}

void BubbleSortLayer::onUpdateGUI(Aquarius::timeDelta_t dt)
{
    if (m_MenuOpen)
    {
        ImGui::Begin("Bubble Sort Demo", &m_MenuOpen);

        if (ImGui::CollapsingHeader("About"))
        {
            ImGui::Text("This application shows a visualization of the Bubble Sort");
            ImGui::Text("- To reset the sort press R on your keyboard");
            ImGui::Text("- To pause the sort press P on your keyboard");
            ImGui::Text("- The delay speed of the sort can be changed under the Configuration Header");
            ImGui::Text("- The bar color can be changed under the Configuration Header");

        }

        if (ImGui::CollapsingHeader("Configuration"))
        {
            ImGui::SliderInt("Delay Speed", &delayConstant, 0, 1000);

            ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_Float;
            ImGui::ColorEdit4("Bar Color##Bar Color", &barColors.x, colorPickerFlags);
        }

        if (ImGui::CollapsingHeader("Profiling"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }

        ImGui::End();
    }
}

void BubbleSortLayer::renderBars(int size)
{
    int position = 0;

    for (int i = 0; i < size; i++)
    {
        Aquarius::Renderer::DrawQuad(
                { position, m_Height - barHeights[i]} ,
                { barWidth, barHeights[i] },
                0,
                barColors
        );

        position += barWidth + 1;
    }
}

void BubbleSortLayer::swapBars(int i, int j)
{
    if (barHeights[i] > barHeights[j])
    {
        std::swap(barHeights[i], barHeights[j]);
        swapped = true;
    }
}
