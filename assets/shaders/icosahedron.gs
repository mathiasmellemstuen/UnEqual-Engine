#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    vec3 v0 = gl_in[0].gl_Position.xyz;
    vec3 v1 = gl_in[1].gl_Position.xyz; 
    vec3 v2 = gl_in[2].gl_Position.xyz;
    vec3 v3 = normalize(0.5 * (v0 + v1));
    vec3 v4 = normalize(0.5 * (v1 + v2));
    vec3 v5 = normalize(0.5 * (v2 + v0));

    mat4 mvp = model * view * projection;

//     0
//   3   5
// 1   4   2

    color = vec3(1.0,1.0,0.0);
    gl_Position = vec4(v0, 1.0);
    EmitVertex();
    gl_Position = vec4(v3, 1.0); 
    EmitVertex();
    gl_Position = vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();

    color = vec3(1.0,0.0,0.0);
    gl_Position = vec4(v3, 1.0); 
    EmitVertex();
    gl_Position = vec4(v1, 1.0); 
    EmitVertex();
    gl_Position = vec4(v4, 1.0); 
    EmitVertex(); 
    EndPrimitive();

    color = vec3(0.0,0.0,1.0);
    gl_Position = vec4(v4, 1.0); 
    EmitVertex();
    gl_Position = vec4(v2, 1.0); 
    EmitVertex();
    gl_Position = vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();

    color = vec3(1.0,0.0,0.0);
    gl_Position = vec4(v3, 1.0); 
    EmitVertex();
    gl_Position = vec4(v4, 1.0); 
    EmitVertex();
    gl_Position = vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();
}