#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec4 color;

uniform mat4 M;
uniform mat4 P;

out vec2 Texcoord;
out vec4 Color;
out vec4 Vertex;

void main()
{
    Vertex = M * vec4(vertex.xyz,1.0);
    Texcoord = texcoord;
    Color = color;
    gl_Position = P * Vertex;
}