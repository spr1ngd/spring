#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out vec3 WorldPos;

void main()
{
    WorldPos = vertex;  
    gl_Position = P * V * M * vec4(vertex,1.0);
}