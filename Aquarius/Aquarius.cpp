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

        // Single Triangle Vertices (NDC)
        std::vector<float> data =
        {
                // Position     // Color
              -0.5f, 0.0f,      0.5f, 0.5f, 0.5f,
               0.0f, 0.5f,      0.5f, 0.5f, 0.5f,
               0.5f, 0.0f,      0.5f, 0.5f, 0.5f,
               0.0f, -0.5f,     0.5f, 0.5f, 0.5f,
        };

        // Rectangle Indices
        std::vector<uint32_t> indices =
        {
            0, 1, 2,    // Triangle 1
            0, 2, 3     // Triangle 2
        };

        auto VB0 = std::make_shared<VertexBuffer>(data.data(), data.size() * sizeof(float));
        auto IB0 = std::make_shared<IndexBuffer>(indices.data(), indices.size());
        auto layout = BufferLayout(
        {
                VertexElement(ShaderType::Float, 2, false),
                VertexElement(ShaderType::Float, 3, false)
        });

        auto VA0 = VertexArray(VB0, IB0, layout);
        VA0.activate();

        // Render loop
        while (1)
        {
            Renderer::ClearColor({0.2, 0.3, 0.7});
            Renderer::Clear();
            Renderer::Submit(&VA0, &shaderProgram);
            Window->OnUpdate();
        }

        return 0;
    }

} // namespace Aquarius
