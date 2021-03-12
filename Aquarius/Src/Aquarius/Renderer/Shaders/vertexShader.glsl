#version 410 core

// Basic Vertex Shader
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 fTexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
   gl_Position = u_projection * u_view * u_model * vec4(aPos.x, aPos.y, 0.0, 1.0);
   fTexCoord = aTexCoord; 
}
