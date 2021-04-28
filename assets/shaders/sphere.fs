#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
uniform vec3 lightPos;
uniform sampler2D diffuse1;
in vec3 normal;
in vec3 fragPosition; 
in vec3 color; 

void main() {

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    vec3 norm = normalize(normal); 
    vec3 lightDir = normalize(lightPos - fragPosition); 
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * color;
    
    vec3 result = (ambient + diffuse) * color;

   FragColor = texture(diffuse1, TexCoords) * vec4(result, 1.0);
}