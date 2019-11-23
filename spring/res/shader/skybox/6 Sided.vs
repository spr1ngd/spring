#version 330 core
layout(location = 0) in vec3 vertex;

// layout (std140) uniform MVP
// {
//     mat4 M;
//     mat4 V;
//     mat4 P;
// }; 

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 V_Vertex;

void main()
{
    V_Vertex = vertex;
    gl_Position = P * V * M * vec4(vertex,1.0);
}