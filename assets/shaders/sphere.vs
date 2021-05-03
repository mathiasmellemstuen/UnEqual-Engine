#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 normal;
out vec3 color;
out vec3 fragPosition;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    color = glm::vec3(0.0,0.7,0.0); 
    fragPosition = aPos; 
    normal = aNormal; 
    TexCoords = vec2(0.0,1.0); 
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}