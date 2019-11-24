#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in mat4 matrix;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;
uniform mat4 LightSpaceMatrix;

uniform vec3 offsets[300];

out vec4 WorldPos;
out vec3 WorldNormal;
out vec2 Texcoord; 
out vec4 LightSpacePos;

void main()
{
    vec3 offset = offsets[gl_InstanceID];
    vec3 pos = vertex + offset;
    WorldPos = M * vec4(pos,1.0);    
    LightSpacePos = LightSpaceMatrix * WorldPos;
    WorldNormal = mat3(NM)*normal;
    Texcoord = texcoord;
    gl_Position = P * V * WorldPos;  
}