#include "Renderer.h"
#include "Aquarius/Core/Application.h"
#include "Aquarius/Renderer/VertexArray.h"

#include <cstdint>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


namespace Aquarius {

        namespace Renderer {

            struct quadRendererInfo
            {
                sharedPtr<VertexArray> vertexArray;
                sharedPtr<Shader> shader;
                glm::vec4 defaultColor = {1,1,1,1};
            };

            static SceneInfo s_SceneData =
            {
                    glm::mat4(1.0f),
                    glm::mat4(1.0f)
            };

            static quadRendererInfo s_QuadData;

            void Init()
            {
                std::vector<float> quadVertices =
                {
                        0.0f, 0.0f, // Bottom left
                        1.0f, 0.0f, // Bottom right
                        1.0f, 1.0f, // Top right
                        0.0f, 1.0f  // Top left
                };

                std::vector<uint32_t> quadIndices =
                {
                        0, 1, 2,
                        2, 3, 0
                };

                // TODO - gross
                auto vertexBuffer = std::make_shared<VertexBuffer>(quadVertices.data(),quadVertices.size() * sizeof(quadVertices[0]));
                auto indexBuffer = std::make_shared<IndexBuffer>(quadIndices.data(), quadIndices.size());
                auto bufferLayout = BufferLayout({
                    VertexElement(ShaderType::Float, 2, false)
                });

                s_QuadData.vertexArray = std::make_shared<VertexArray>(vertexBuffer, indexBuffer, bufferLayout);
                s_QuadData.shader = std::make_unique<Shader>("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
            }

            void Shutdown()
            {
                // Nothing to put here just yet
            }

            void setProjection(const glm::mat4& projection)
            {
                s_SceneData.projection = projection;
            }

            void setView(const glm::mat4& view)
            {
                s_SceneData.projection = view;
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
