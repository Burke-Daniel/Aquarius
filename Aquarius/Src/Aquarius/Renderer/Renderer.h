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

        void SetView(const glm::mat4& view);
        void SetProjection(const glm::mat4& projection);

        void Submit(VertexArray* vertexArray, Shader* shader);
        void DrawQuad(const glm::vec2& pos, 
                      const glm::vec2& size, 
                      float rotationDegrees = 0.0f, 
                      const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 1.0f });

    } // namespace Renderer

} // namespace Aquarius
