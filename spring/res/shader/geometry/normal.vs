#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out VS_OUT
{
    vec3 WorldNormal;
} vs_out;

void main()
{
    vec4 worldNormal = NM * vec4(normal.xyz,1.0);
    vs_out.WorldNormal = (P * worldNormal).xyz;
    gl_Position = P * V * M * vec4(vertex,1.0);
}