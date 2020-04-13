#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;

uniform mat4 MVP;

out VS_OUT
{
    vec4 pos;
} vs_out;

void main()
{
    vs_out.pos = MVP * vec4(vertex,1.0);
    gl_Position = MVP * vec4(vertex,1.0);
}