#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;

uniform mat4 M;
uniform mat4 P;

out vec3 WorldPos;
out vec2 Texcoord;

void main()
{
    WorldPos = mat3(M) * vertex;
    Texcoord = texcoord;
    gl_Position = P * vec4(WorldPos,1.0);
}