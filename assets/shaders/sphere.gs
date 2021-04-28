#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec3 normal;
out vec3 fragPosition;
out vec2 TexCoords; 

vec3 calculateNormal(in vec3 v1, in vec3 v2, in vec3 v3) {
    vec3 crossed = cross(vec3(v3 - v1), vec3(v2 - v1));
    float len = length(crossed);
    return -1.0 * crossed / len;  
}

void main() {

    vec3 v0 = gl_in[0].gl_Position.xyz;
    vec3 v1 = gl_in[1].gl_Position.xyz; 
    vec3 v2 = gl_in[2].gl_Position.xyz;

    mat4 mvp = projection * view * model;
    color = vec3(0.0,0.7,0.0);

    normal = calculateNormal(v0, v1, v2);

    TexCoords = vec2(1.0,1.0);
    fragPosition = v0;
    gl_Position = mvp * vec4(v0, 1.0);
    EmitVertex();
    TexCoords = vec2(0.0,1.0);
    fragPosition = v1;
    gl_Position = mvp * vec4(v1, 1.0); 
    EmitVertex();
    TexCoords = vec2(0.0,0.0);
    fragPosition = v2;
    gl_Position = mvp * vec4(v2, 1.0); 
    EmitVertex(); 
    EndPrimitive();

}