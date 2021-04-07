#include "Sandbox.h"
#include "RPG/LevelEditorLayer.h"

#include "IntroLayer.h"
#include "BubbleSortLayer.h"
#include "ManagerLayer.h"
#include "PongLayer.h"

#include <glm/gtc/matrix_transform.hpp>

//static void ShowPlaceholderObject(const char* prefix, int uid);
static void ShowEntity(const char* prefix, Entity* entity);

SandboxLayer::SandboxLayer()
    : Layer("Sandbox", true)
{}

SandboxLayer::~SandboxLayer()
{
    for (const auto* entity : m_entities)
    {
        delete entity;
    }
}

void SandboxLayer::onCreation()
{
    Aquarius::Application* app = Aquarius::Application::get();
    Aquarius::Window* window = app->getWindow();

    int height = window->getHeight();
    int width = window->getWidth();

    m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

    Aquarius::TextureConfiguration texConfig = {
        Aquarius::TextureWrapOption::Repeat,
        Aquarius::TextureWrapOption::Repeat,
        Aquarius::TextureFilteringOption::Linear,
        Aquarius::TextureFilteringOption::Linear
    };

    // Textures / spritesheets
    // m_texture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/greenguy.png", texConfig, true);
    m_texture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/mun-logo.png", texConfig, true);
    m_texture->bind(0);

    m_spritesheet = std::make_unique<Aquarius::SpriteSheet>(m_texture.get(), 32, 32);
    m_uv = m_spritesheet->getSpriteCoords(0, 1);

    // Create list of entities
    m_entities = std::vector<Entity*>();
    
    Entity* ent = new Entity(
        { 0,0 },
        { 32,32 },
        { 1,1,1,1 },
        0
    );

    m_entities.push_back(ent);

    for (int i = 0; i < 10; i++)
    {
        Entity* ent = new Entity(
            { rand() % 800, rand() % 600},
            { 32, 32 },
            {(rand() % 255 ) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0, 1},
            0
        );
        m_entities.push_back(ent);
    }

    Aquarius::Renderer::Init();
}

void SandboxLayer::onUpdate(Aquarius::timeDelta_t ts)
{
    m_Camera->onUpdate(ts);
    glm::vec3 cameraPos = m_Camera->getPosition();
    Aquarius::Renderer::BeginScene(m_Camera.get());
    Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
    Aquarius::Renderer::Clear();

    // Draw each entity
    for (auto entity : m_entities)
    {
        entity->onUpdate(ts);
        entity->draw();
    }
    
    if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_m))
    {
        m_MenuOpen = true;
    }
}

void SandboxLayer::onUpdateGUI(Aquarius::timeDelta_t ts)
{
    ImVec2 ButtonSize = { 200, 20 };
    Aquarius::Application* app = Aquarius::Application::get();
    int screenW = app->getWindow()->getWidth();
    int screenH = app->getWindow()->getHeight();
    static float cameraMoveSpeed = 1;
    static float cameraZoomSpeed = 0.1;
    static int maxRandEntityWidth = 32;
    static int maxRandEntityHeight = 32;
    static float randomEntityAnimSpeed = 0.1;
    static bool animateRandomEntities = false;
    static glm::vec2 customEntityPosition = {0, 0};
    static glm::vec2 customEntityScale = {32, 32};
    static glm::vec4 customEntityColor = { 0, 0, 0, 1 };
    static bool customEntityIsAnimated = false;
    static float customEntityAnimSpeed = 0.1;

    if (m_MenuOpen)
    {
        ImGui::Begin("Sandbox Demo", &m_MenuOpen);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Sandbox Demo!");

        if (ImGui::CollapsingHeader("About"))
        {
            ImGui::Text("This is a sandbox where various features of the engine are tested");
            ImGui::Text("- WASD Moves the camera around");
            ImGui::Text("- Arrow up/down to zoom in and out");
            ImGui::Text("- Initially, there are 10 entities randomly rendered");
            ImGui::Text("- Entities can be:");
            ImGui::Text("   - Added one at a time");
            ImGui::Text("   - Popped one at a time");
            ImGui::Text("   - Added in bulk (N at a time)");
            ImGui::Text("   - Cleared (nuked)");
            ImGui::NewLine();
        }

        if (ImGui::CollapsingHeader("Configuration"))
        {
            ImGui::PushItemWidth(200);
            ImGui::Text("To aid the demo, a couple of options are configurable here!");

            ImGui::SliderInt("Max Random Entity Height", &maxRandEntityHeight, 32, screenH);
            ImGui::SliderInt("Max Random Entity Width", &maxRandEntityWidth, 32, screenW);
            ImGui::SliderFloat("Random Entity Anim Speed", &randomEntityAnimSpeed, 0, 1);
            ImGui::Checkbox("Animate Random Entities?", &animateRandomEntities);

            ImGui::SliderFloat("Camera Move Speed", &cameraMoveSpeed, 0, 5);
            ImGui::SliderFloat("Camera Zoom Speed", &cameraZoomSpeed, 0, 0.3);

            m_Camera->setMoveSpeed(cameraMoveSpeed);
            m_Camera->setZoomSpeed(cameraZoomSpeed);

            if (ImGui::CollapsingHeader("Custom Entity Configuration"))
            {
                // LOOK: Can spawn items off screen because max is same for height and width
                ImGui::SliderFloat2("Entity Position", &(customEntityPosition.x), 0, screenW);
                ImGui::SliderFloat2("Entity Scale", &customEntityScale.x, 0, screenW);
                ImGui::ColorPicker4("Entity Color", &customEntityColor.x);
                ImGui::SliderFloat("Entity Anim Speed", &customEntityAnimSpeed, 0, 1);
                ImGui::Checkbox("Animate?", &customEntityIsAnimated);

                ImGui::NewLine();
            }

            ImGui::NewLine();
        }

        if (ImGui::CollapsingHeader("Controls"))
        {
            if (ImGui::Button("Generate Custom Entity", ButtonSize))
            {
                Entity* ent = new Entity(
                    customEntityPosition,
                    customEntityScale,
                    customEntityColor,
                    0,
                    customEntityIsAnimated
                );
                ent->m_animationSpeed = customEntityAnimSpeed;
                m_entities.push_back(ent);
            }

            if (ImGui::Button("Generate Random Entity", ButtonSize))
            {   
                int w = rand() % maxRandEntityWidth;
                int h = rand() % maxRandEntityHeight;

                Entity* ent = new Entity(
                    { rand() % screenW-w, rand() % screenH-h},
                    { w, h },
                    { (rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0, 1 },
                    0,
                    animateRandomEntities
                );
                ent->m_animationSpeed = randomEntityAnimSpeed;
                m_entities.push_back(ent);
            }

            if (ImGui::Button("Pop Single Entity", ButtonSize))
            {
                if (m_entities.size() != 0)
                {
                    Entity* ent = m_entities.back();
                    delete ent;
                    ent = nullptr;
                    m_entities.pop_back();
                }
                else
                {
                    ImGui::Text("No Entities!");
                }

            }
            
            static int numEntities;
            static int numEntitiesToPop;

            if (ImGui::Button("Generate N Entities (32x32)", ButtonSize))
            {
                for (int i = 0; i < numEntities; i++)
                {
                    Entity* ent = new Entity(
                        { rand() % screenW, rand() %  screenH},
                        { 32, 32 },
                        { (rand() % 255) / 255.0, (rand() % 255) / 255.0, (rand() % 255) / 255.0, 1 },
                        0,
                        animateRandomEntities
                    );
                    m_entities.push_back(ent);

                    ent->m_animationSpeed = randomEntityAnimSpeed;
                }
            }

            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderInt("N##1", &numEntities, 0, 1000);

            if (ImGui::Button("Pop N Entities", ButtonSize))
            {
                // TODO - Make it so you can configure the entity
                if (numEntitiesToPop <= m_entities.size())
                {
                    for (int i = 0; i < numEntitiesToPop; i++)
                    {
                        Entity* ent = m_entities.back();
                        delete ent;
                        ent = nullptr;
                        m_entities.pop_back();
                    }
                }

            }

            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            ImGui::SliderInt("N##2", &numEntitiesToPop, 0, m_entities.size());

            if (ImGui::Button("Clear All Entities", ButtonSize))
            {
                if (m_entities.size() != 0)
                {
                    for (auto ent : m_entities)
                    {
                        delete ent;
                    }
                    m_entities.clear();
                }
            }

            if (ImGui::Button("Home Camera", ButtonSize))
            {
                m_Camera->setPosition({ 0, 0, -1});
            }

            ImGui::NewLine();
        }

        if (ImGui::CollapsingHeader("Entity Viewer"))
        {

            ImGui::Text("Entities: %i", m_entities.size());
            static bool showPropertyEditor = false;
            if (ImGui::Button("Open Property Viewer"))
            {
                showPropertyEditor = true;
            }

            if (showPropertyEditor)
            {
                ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
                if (!ImGui::Begin("Entity Property Editor", &showPropertyEditor))
                {
                    ImGui::End();
                    return;
                }

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
                if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
                {
                    // Iterate placeholder objects (all the same data)
                    for (auto* entity : m_entities)
                    {
                        ShowEntity("Entity", entity);
                    }
                    ImGui::EndTable();
                }
                ImGui::PopStyleVar();
                ImGui::End();
            }
            ImGui::NewLine();
        }

        if (ImGui::CollapsingHeader("Profiling"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
            ImGui::NewLine();
        }

        if (ImGui::CollapsingHeader("Texture Preview"))
        {
            ImGui::Text("Demo Only");

            // size, uv0, uv1
            ImGui::Image(
                (void*)(intptr_t)m_texture->getID(), 
                ImVec2(128, 
                       128),
                ImVec2(0,1),
                ImVec2(1,0)
            );
            ImGui::NewLine();
        }

        ImGui::End();
    }
}

Sandbox::Sandbox()
    : Aquarius::Application("Sandbox")
{
    Aquarius::Log::setLogLevel(Aquarius::LogLevel::Info);

    auto introLayer = PushLayer(std::make_unique<IntroLayer>());
    auto pongLayer = PushLayer(std::make_unique<PongLayer>());
    auto bubbleSortLayer = PushLayer(std::make_unique<BubbleSortLayer>());
    auto rpgLayer = PushLayer(std::make_unique<LevelEditorLayer>());
    auto sandboxLayer = PushLayer(std::make_unique<SandboxLayer>());

    PushLayer(std::make_unique<ManagerLayer>(
        std::vector<Aquarius::Layer*>{ introLayer, pongLayer, bubbleSortLayer, rpgLayer, sandboxLayer}));
    
}

Aquarius::uniquePtr<Aquarius::Application> createApplication()
{
    return std::make_unique<Sandbox>();
}


static void ShowEntity(const char* prefix, Entity* entity)
{
    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
    ImGui::PushID(entity->m_id);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool node_open = ImGui::TreeNode("Entity", "%s_%u", prefix, entity->m_id);
    ImGui::TableSetColumnIndex(1);


    if (node_open)
    {
        // POSITION
        ImGui::PushID("Position"); // Use field index as identifier.
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        ImGui::TreeNodeEx("Field", flags, "Position");

        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat2("Position##Position", &(entity->m_position.x), 0.0f, 1000);
        ImGui::NextColumn();
        ImGui::PopID();

        // SCALE
        ImGui::PushID("Scale"); 
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TreeNodeEx("Field", flags, "Scale");
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat2("Scale##Scale", &(entity->m_scale.x), 0.0f, 1000.0f);
        ImGui::NextColumn();
        ImGui::PopID();

        // ROTATION
        ImGui::PushID("Rotation"); 
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TreeNodeEx("Field", flags, "Rotation");
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("Rotation##Rotation", &(entity->m_rotation), 0.0f, 360.0f);
        ImGui::NextColumn();
        ImGui::PopID();

        // COLOR
        ImGui::PushID("Color"); 
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TreeNodeEx("Field", flags, "Color");
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);

        ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_Float;
        ImGui::ColorEdit4("Color##Color", &(entity->m_color.x), colorPickerFlags);
        ImGui::NextColumn();
        ImGui::PopID();

        // Animation Speed
        ImGui::PushID("Animation Speed");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TreeNodeEx("Field", flags, "Animation Speed");
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("AnimationSpeed##AnimationSpeed", &entity->m_animationSpeed, 0, 1);
        ImGui::NextColumn();
        ImGui::PopID();

        // Animated
        ImGui::PushID("Animated");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TreeNodeEx("Field", flags, "Animated");
        ImGui::AlignTextToFramePadding();
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::Checkbox("Animated##Animated", &entity->m_isAnimated);
        ImGui::NextColumn();
        ImGui::PopID();

        ImGui::TreePop();
    }
    ImGui::PopID();
}
