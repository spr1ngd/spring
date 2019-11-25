#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in mat4 matrix;


uniform mat4 V;
uniform mat4 P;
uniform mat4 LightSpaceMatrix;

out VS_OUT
{
    vec3 WorldNormal;
} vs_out;

void main()
{
    mat4 nm = inverse(transpose(matrix));
    vec4 worldNormal = nm * vec4(normal.xyz,1.0);
    vs_out.WorldNormal = (P * worldNormal).xyz;
    gl_Position = P * V * matrix * vec4(vertex,1.0);
}