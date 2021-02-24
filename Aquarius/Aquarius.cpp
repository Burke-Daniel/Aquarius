#define AQ_ASSERT_ENABLE

#include "Aquarius.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Window.h"
#include "Aquarius/Core/Assert.h"
#include "Aquarius/Renderer/VertexBuffer.h"
#include "Aquarius/Renderer/IndexBuffer.h"


namespace Aquarius {

    int Test::testMain()
    {
        Log::initLoggers();

        std::unique_ptr<Window> Window = Window::Create(800, 600, "Aquarius");
        Window->Initialize();

        AQ_INFO("Testing %v %v", "client", "logger");
        AQ_CORE_INFO("Testing %v %v", "core", "logger");

        while (1)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            Window->OnUpdate();
        }

        return 0;
    }

    int Test::triangleTest()
    {
        // Init logging
        Log::initLoggers();

        // Create Window
        std::unique_ptr<Window> Window = Window::Create(800, 600, "Aquarius");
        Window->Initialize();

        // Single Triangle Vertices (NDC - Just Pos)
        std::vector<float> data =
        {
                // position
              -0.5f, 0.0f, 0.0f,
               0.0f, 0.5f, 0.0f,
               0.5f, 0.0f, 0.0f,
               0.0f, -0.5f, 0.0f
        };

        // Rectangle Indices
        std::vector<uint32_t> indices =
        {
            0, 1, 2,    // Triangle 1
            0, 2, 3     // Triangle 2
        };

        // TODO - Create vertex array abstraction
        uint32_t VA0;
        glGenVertexArrays(1, &VA0);
        glBindVertexArray(VA0);

        // Create and bind vertex buffer
        VertexBuffer VB0 = VertexBuffer(data.data(), data.size() * sizeof(data[0]));
        VB0.Bind();

        // Create and bind index buffer
        IndexBuffer IB0 = IndexBuffer(indices.data(), indices.size());
        IB0.Bind();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Render loop
        while (1)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0);
            Window->OnUpdate();
        }

        return 0;
    }
} // namespace Aquarius

