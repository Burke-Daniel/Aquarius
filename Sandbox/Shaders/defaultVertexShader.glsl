#version 410 core

// Basic Vertex Shader
layout (location = 0) in vec2 aPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
   gl_Position = u_projection * u_view * u_model * (aPos.x, aPos.y, 0.0, 1.0);
}
