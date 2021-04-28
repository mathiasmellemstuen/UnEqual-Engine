#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec3 normal;
out vec3 fragPosition;

vec3 calculateNormal(in vec3 v1, in vec3 v2, in vec3 v3) {
    vec3 crossed = cross(vec3(v3 - v1), vec3(v2 - v1));
    float len = length(crossed);
    return -1.0 * crossed / len;  
}

void main() {

    vec3 v0 = gl_in[0].gl_Position.xyz;
    vec3 v1 = gl_in[1].gl_Position.xyz; 
    vec3 v2 = gl_in[2].gl_Position.xyz;
    vec3 v3 = normalize(0.5 * (v0 + v1));
    vec3 v4 = normalize(0.5 * (v1 + v2));
    vec3 v5 = normalize(0.5 * (v2 + v0));

    mat4 mvp = projection * view * model;

//     0
//   3   5
// 1   4   2
    color = vec3(0.9,0.0,0.0);

    normal = calculateNormal(v0, v3, v5);

    fragPosition = v0;
    gl_Position = mvp * vec4(v0, 1.0);
    EmitVertex();

    fragPosition = v3;
    gl_Position = mvp * vec4(v3, 1.0); 
    EmitVertex();

    fragPosition = v5;
    gl_Position = mvp * vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();

    normal = calculateNormal(v3,v1,v4); 

    fragPosition = v3;
    gl_Position = mvp * vec4(v3, 1.0); 
    EmitVertex();

    fragPosition = v1;
    gl_Position = mvp * vec4(v1, 1.0); 
    EmitVertex();

    fragPosition = v4;
    gl_Position = mvp * vec4(v4, 1.0); 
    EmitVertex(); 
    EndPrimitive();

    normal = calculateNormal(v4,v2,v5); 

    fragPosition = v4;
    gl_Position = mvp * vec4(v4, 1.0); 
    EmitVertex();

    fragPosition = v2;
    gl_Position = mvp * vec4(v2, 1.0); 
    EmitVertex();

    fragPosition = v5;
    gl_Position = mvp * vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();
    
    normal = calculateNormal(v3,v4,v5); 

    fragPosition = v3;
    gl_Position = mvp * vec4(v3, 1.0); 
    EmitVertex();
    fragPosition = v4;
    gl_Position = mvp * vec4(v4, 1.0); 
    EmitVertex();
    fragPosition = v5;
    gl_Position = mvp * vec4(v5, 1.0); 
    EmitVertex(); 
    EndPrimitive();
}