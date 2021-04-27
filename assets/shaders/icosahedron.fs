#version 330 core
out vec4 FragColor;

uniform vec3 lightPos;

in vec3 color;
in vec3 normal;
in vec3 fragPosition; 

void main() {

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    vec3 norm = normalize(normal); 
    vec3 lightDir = normalize(lightPos - fragPosition); 
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * color;
    
    vec3 result = (ambient + diffuse) * color;

    FragColor = vec4(result, 1.0);
}