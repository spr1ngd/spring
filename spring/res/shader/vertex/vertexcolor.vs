#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec4 color;

// layout (std140) uniform MVP
// {
//     mat4 M;
//     mat4 V;
//     mat4 P;
// }; 

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 Texcoord;
out vec4 VertexColor;

void main()
{
    Texcoord = texcoord;
    VertexColor = color;
    gl_Position = P * V * M * vec4(vertex,1.0);
}