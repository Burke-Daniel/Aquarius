#version 410 core

// Modifiable Fragment Shader
out vec4 FragColor;
in vec3 fColor;
in vec2 fTexCoord;

uniform sampler2D fTexture;

void main()
{
     FragColor = texture(fTexture, fTexCoord) * vec4(fColor, 1.0); 
<<<<<<< HEAD
}
=======
}
>>>>>>> 01dbdf6 (Remove default shaders from Sandbox and place them in Src/Renderer, add back sandbox shader that got merc'd by rebase somehow)
