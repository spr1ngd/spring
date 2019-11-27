#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 3) in mat4 matrix;

uniform mat4 V;
uniform mat4 P;

void main()
{
    vec4 WorldPos = matrix * vec4(vertex,1.0);    
    gl_Position = P * V * WorldPos;  
}