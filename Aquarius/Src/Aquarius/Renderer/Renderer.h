#pragma once

#include "Aquarius/Renderer/VertexArray.h"
#include "Aquarius/Renderer/IndexBuffer.h"
#include "Aquarius/Renderer/Shader.h"

#include <glm/glm.hpp>


namespace Aquarius {

    namespace Renderer {

        void Init();
        void Shutdown();

        void Clear();
        void ClearColor(glm::vec3 color);

        void Submit(VertexArray* vertexArray, Shader* shader);

    } // namespace Renderer

} // namespace Aquarius
