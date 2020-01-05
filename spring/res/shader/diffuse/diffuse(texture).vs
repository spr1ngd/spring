#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out vec3 Normal;
out vec2 Texcoord;

void main()
{
    Texcoord = texcoord;
    Normal = mat3(NM) * normal;
    gl_Position = P * V * M * vec4(vertex,1.0);
}