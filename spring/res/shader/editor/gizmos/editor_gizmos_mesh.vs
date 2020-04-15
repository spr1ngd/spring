#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;

uniform mat4 M;
uniform mat4 MVP;
out vec2 Texcoord;
out vec4 WorldPos;

void main()
{
    Texcoord = texcoord;
    WorldPos = M * vec4(vertex,1.0);
    gl_Position = MVP * vec4(vertex,1.0);
}