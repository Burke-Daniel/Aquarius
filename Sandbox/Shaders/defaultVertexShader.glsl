#version 410 core

// Basic Vertex Shader
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fColor;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
   fColor = aColor;
}
