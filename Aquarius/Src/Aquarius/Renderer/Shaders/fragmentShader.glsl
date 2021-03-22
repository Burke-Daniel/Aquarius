#version 410 core

// Basic Fragment Shader
out vec4 FragColor;
in vec2 fTexCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
     FragColor = texture(u_texture, fTexCoord) * u_color;
}
