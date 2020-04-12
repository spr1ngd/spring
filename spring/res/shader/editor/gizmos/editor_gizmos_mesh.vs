#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertex,1.0);
}