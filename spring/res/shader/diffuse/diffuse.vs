#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out vec4 WorldPos;
out vec3 WorldNormal;
out vec2 Texcoord;

void main()
{
    WorldPos = M * vec4(vertex,1.0);    
    WorldNormal = mat3(NM)*normal;
    Texcoord = texcoord;
    gl_Position = P * V * WorldPos;    
}