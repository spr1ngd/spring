#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texcoord;

out vec2 Texcoord;

void main()
{
    Texcoord = texcoord;
    gl_Position = vec4(vertex,1.0);
}