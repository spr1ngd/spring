#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 MVP;
uniform float outlineWidth;

void main()
{
    vec3 pos = vertex + normal * outlineWidth;
    gl_Position = MVP * vec4(pos,1.0);
}