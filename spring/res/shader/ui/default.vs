#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec4 color;

out vec2 Texcoord;
out vec4 Color;

void main()
{
    Texcoord = texcoord;
    Color = color;
    gl_Position = vec4(vertex,1.0);
}