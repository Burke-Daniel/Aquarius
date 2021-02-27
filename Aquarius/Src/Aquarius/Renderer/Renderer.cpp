#include "Renderer.h"
#include "Aquarius/Core/Application.h"

#include <glad/glad.h>


namespace Aquarius {

        namespace Renderer {

            void Init()
            {
                glPolygonMode(GL_FRONT, GL_FILL);
            }

            void Shutdown()
            {
                // Nothing to put here just yet
            }

            void Clear()
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            void ClearColor(glm::vec3 color)
            {
                glClearColor(color.x, color.y, color.z, 1.0f);
            }

            void Submit(VertexArray* vertexArray, Shader* shader)
            {
                shader->activate();
                vertexArray->activate();
                glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, (void*)0);
            }

        } // namespace Renderer

} // namespace Aquarius
