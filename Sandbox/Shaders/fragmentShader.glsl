#version 410 core

// Basic Fragment Shader
out vec4 FragColor;

uniform vec4 u_color;

void main()
{
     FragColor = u_color;
}
