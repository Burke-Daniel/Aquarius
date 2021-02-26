#pragma once

#include "Aquarius/Renderer/VertexArray.h"
#include "Aquarius/Renderer/IndexBuffer.h"
#include "Aquarius/Renderer/Shader.h"

#include <glm/glm.hpp>


namespace Aquarius {

    class Renderer
    {
    public:
        Renderer() = delete;
        ~Renderer() = delete;

        static void Init();
        static void Shutdown();

        static void Clear();
        static void ClearColor(glm::vec3 color);

        static void Submit(VertexArray* vertexArray, Shader* shader);
    };

}
