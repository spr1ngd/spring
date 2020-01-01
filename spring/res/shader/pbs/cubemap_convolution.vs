#version 330 core

layout (location = 0) in vec3 vertex;

out vec3 WorldPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    WorldPos = vertex;
    gl_Position = P * V * M * vec4(vertex,1.0);
}