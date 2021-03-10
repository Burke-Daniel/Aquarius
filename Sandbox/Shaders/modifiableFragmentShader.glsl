#version 410 core

// Modifiable Fragment Shader
out vec4 FragColor;
in vec3 fColor;
in vec2 fTexCoord;

uniform sampler2D fTexture;

void main()
{
     FragColor = texture(fTexture, fTexCoord) * vec4(fColor, 1.0); 
}
