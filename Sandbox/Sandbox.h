#pragma once

#include <Aquarius.h>

#include <array>

class SandboxLayer : public Aquarius::Layer
{
public:
	SandboxLayer(const std::string& vertexShader, const std::string& fragmentShader);

	void onCreation() override;
	void onUpdate(Aquarius::timeDelta_t time) override;

private:
	Aquarius::sharedPtr<Aquarius::Shader> m_ShaderProgram;
	Aquarius::sharedPtr<Aquarius::VertexBuffer> m_vertexBuffer;
	Aquarius::sharedPtr<Aquarius::IndexBuffer> m_indexBuffer;
	Aquarius::sharedPtr<Aquarius::BufferLayout> m_bufferLayout;
	Aquarius::sharedPtr<Aquarius::VertexArray> m_vertexArray;

	std::array<float, 5 * 4> m_triangleVertices =
	{
		// Position     // Color
	  -0.5f, 0.0f,      0.5f, 0.5f, 0.5f,
	   0.0f, 0.5f,      0.5f, 0.5f, 0.5f,
	   0.5f, 0.0f,      0.5f, 0.5f, 0.5f,
	   0.0f, -0.5f,     0.5f, 0.5f, 0.5f,
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
