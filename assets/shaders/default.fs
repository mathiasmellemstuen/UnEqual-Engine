#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2; 

vec2 tex1 = vec2(0.0, 1.0);

void main()
{    
    FragColor = texture(diffuse1, TexCoords);
};