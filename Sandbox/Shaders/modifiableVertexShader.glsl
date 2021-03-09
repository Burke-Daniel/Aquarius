#version 410 core

// Modifiable Vertex Shader
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
   fColor = aColor;
   fTexCoord = aTexCoord;
}
