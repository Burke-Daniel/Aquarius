#pragma once

#include "Aquarius.h"
#include "Entity.h"

#include <array>

class SandboxLayer : public Aquarius::Layer
{
public:
	SandboxLayer();
	~SandboxLayer();

	void onCreation() override;
	void onUpdate(Aquarius::timeDelta_t time) override;
	void onUpdateGUI(Aquarius::timeDelta_t time) override;

private:
	bool m_MenuOpen = true;

	Aquarius::sharedPtr<Aquarius::Shader> m_ShaderProgram;
	Aquarius::sharedPtr<Aquarius::VertexBuffer> m_vertexBuffer;
	Aquarius::sharedPtr<Aquarius::IndexBuffer> m_indexBuffer;
	Aquarius::sharedPtr<Aquarius::BufferLayout> m_bufferLayout;
	Aquarius::sharedPtr<Aquarius::VertexArray> m_vertexArray;
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
	Aquarius::sharedPtr<Aquarius::Texture> m_texture;
	
	std::vector<Entity*> m_entities;
	Aquarius::uniquePtr<Aquarius::SpriteSheet> m_spritesheet;

	// Tex coords
	Aquarius::QuadTexCoords m_uv;

	std::array<float, 7 * 4> m_triangleVertices =
	{
		// Position     // Color			// Texture Coords
	   0.5f, 0.5f,      0.5f, 0.5f, 0.5f,	1.0f, 1.0f,
	   0.5f, -0.5f,     0.5f, 0.5f, 0.5f,	1.0f, 0.0f,
	   -0.5f, -0.5f,    0.5f, 0.5f, 0.5f,	0.0f, 0.0f,
	   -0.5f, 0.5f,     0.5f, 0.5f, 0.5f,	0.0f, 1.0f
	};

	std::array<uint32_t, 3 * 2> m_indices =
	{
		0, 1, 2,    // Triangle 1
		0, 2, 3     // Triangle 2
	};
};

class Sandbox : public Aquarius::Application
{
public:
	Sandbox();
};

Aquarius::Application::ApplicationPtr createApplication();
