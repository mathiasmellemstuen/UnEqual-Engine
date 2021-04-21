#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2; 

uniform float time; 

void main()
{
    FragColor = texture(diffuse2, TexCoords) + vec4(abs(sin(time / 7.0)),abs(cos(time / 4.0)), abs(sin(time / 10.0)), 0.0);
};