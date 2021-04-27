#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

in vec3 normals[];
in vec3 fragPositions[]; 

out vec3 normal; 
out vec3 fragPosition;
out vec3 color; 

void main() {   

    vec3 top = gl_in[0].gl_Position; 
    vec3 bottom1 = gl_in[1].gl_Position;
    vec3 bottom2 = gl_in[2].gl_Position;
    vec3 bottomMiddle = bottom1 / bottom2; 

    vec3 vertexMidPoint1 = vec3(gl_in[0].gl_Position.x / gl_in[1].gl_Position.x, gl_in[0].gl_Position.y / gl_in[1].gl_Position.y, gl_in[0].gl_Position.z / gl_in[1].gl_Position.z); 
    vec3 vertexMidPoint2 = vec3(gl_in[0].gl_Position.x / gl_in[2].gl_Position.x, gl_in[0].gl_Position.y / gl_in[2].gl_Position.y, gl_in[0].gl_Position.z / gl_in[2].gl_Position.z); 
    

    gl_Position = top; 
    normal = normals[0]; 
    fragPosition = fragPositions[0]; 
    EmitVertex(); 
    gl_Position = vertexMidPoint1;
    normal = normals[0]; 
    fragPosition = fragPositions[0]; 
    EmitVertex();
    gl_Position = vertexMidPoint2;
    normal = normals[0]; 
    fragPosition = fragPositions[0]; 
    EmitVertex();  
    EndPrimitive(); 

    gl_Position = vertexMidPoint1; 
    normal = normals[1]; 
    fragPosition = fragPositions[1]; 
    EmitVertex(); 
    gl_Position = bottom1;
    normal = normals[1]; 
    fragPosition = fragPositions[1]; 
    EmitVertex();
    gl_Position = bottomMiddle;
    normal = normals[1]; 
    fragPosition = fragPositions[1]; 
    EmitVertex();  
    EndPrimitive();

    gl_Position = vertexMidPoint2; 
    normal = normals[2]; 
    fragPosition = fragPositions[2]; 
    EmitVertex(); 
    gl_Position = bottom2;
    normal = normals[2]; 
    fragPosition = fragPositions[2]; 
    EmitVertex();
    gl_Position = bottomMiddle;
    normal = normals[2]; 
    fragPosition = fragPositions[2]; 
    EmitVertex();
    EndPrimitive(); 
    // gl_Position = gl_in[0].gl_Position;
    // normal = normals[0]; 
    // fragPosition = fragPositions[0];
    // color = vec3(0, 1.0, 0.0);
    // EmitVertex();
    // gl_Position = gl_in[1].gl_Position;
    // normal = normals[1]; 
    // fragPosition = fragPositions[1]; 
    // color = vec3(1.0, 0.0, 0.0);
    // EmitVertex(); 
    // gl_Position = gl_in[2].gl_Position;
    // normal = normals[2]; 
    // fragPosition = fragPositions[2]; 
    // color = vec3(0.0, 0.0, 1.0);
    // EmitVertex();
    // EndPrimitive(); 
}