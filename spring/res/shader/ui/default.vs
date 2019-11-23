#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec4 color;

// layout (std140) uniform MVP
// {
//     mat4 M;
//     mat4 V;
//     mat4 P;
// }; 

uniform mat4 M;
uniform mat4 P;

out vec2 Texcoord;
out vec4 Color;

void main()
{
    Texcoord = texcoord;
    Color = color;
    gl_Position = P * M * vec4(vertex.xy,0.0,1.0);
}