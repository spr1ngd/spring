#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 M;
uniform mat4 MVP;
uniform vec3 WorldSpaceCameraPos;

uniform vec3 WorldSpaceAxisPos;
const float rate = 5;

void main()
{
    vec3 offset = WorldSpaceCameraPos - WorldSpaceAxisPos;
    float d = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
    float realRate = d / 5;
    gl_Position = MVP * vec4(vertex * realRate,1.0);
}