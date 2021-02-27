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

            void SetProjection(const glm::mat4& projection)
            {
                s_SceneData.projection = projection;
            }

            void SetView(const glm::mat4& view)
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

            void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotationDegrees = 0.0, const glm::vec4& color = s_QuadData.defaultColor)
            {
                // Configure model matrix
                glm::mat4 model = glm::mat4(1.0f);

                // Translate to the correct position
                model = glm::translate(model, {pos.x, pos.y, 0.0f});

                // Translate to center of quad, rotate, shift back
                model = glm::translate(model, {size.x/2.0, size.y/2.0, 0.0f});
                model = glm::rotate(model, glm::radians(rotationDegrees), {0.0f,0.0f,1.0f});
                model = glm::translate(model, {-size.x/2, -size.y/2, 0.0f});

                // Scale
                model = glm::scale(model, {size.x, size.y, 1.0f});

                s_QuadData.vertexArray->activate();
                s_QuadData.shader->activate();
                s_QuadData.shader->setMat4("u_model", false, model);
                s_QuadData.shader->setMat4("u_view", false, s_SceneData.view);
                s_QuadData.shader->setMat4("u_model", false, s_SceneData.projection);
                s_QuadData.shader->setFloat4("u_color", color);

                // Finally draw the quad
                glDrawElements(GL_TRIANGLES, s_QuadData.vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, (void*)0);
            }

        } // namespace Renderer

} // namespace Aquarius
