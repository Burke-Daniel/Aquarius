#define AQ_ASSERT_ENABLE

#include "Aquarius.h"


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

        // Create shader
        auto shaderProgram = Shader("Shaders/vertexShader.glsl",
                                      "Shaders/fragmentShader.glsl");
        
        // Bind shader
        shaderProgram.activate();

        // Single Triangle Vertices (NDC - Just Pos)
        std::vector<float> data =
        {
                // position
              -0.5f, 0.0f,
               0.0f, 0.5f,
               0.5f, 0.0f,
               0.0f, -0.5f
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
        VertexBuffer VB0 = VertexBuffer(data.data(), data.size() * sizeof(float));
        VB0.Bind();

        // Create and bind index buffer
        IndexBuffer IB0 = IndexBuffer(indices.data(), indices.size());
        IB0.Bind();

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Render loop
        while (1)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            shaderProgram.setFloat4("color", {1.0f, 1.0f, 1.0f, 1.0f});
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
            Window->OnUpdate();
        }

        return 0;
    }
} // namespace Aquarius

