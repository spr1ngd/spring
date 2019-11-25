#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in mat4 matrix;


uniform mat4 V;
uniform mat4 P;
uniform mat4 LightSpaceMatrix;

out vec4 WorldPos;
out vec3 WorldNormal;
out vec2 Texcoord; 
out vec4 LightSpacePos;

void main()
{
    mat4 nm = inverse(transpose(matrix));
    WorldPos = matrix * vec4(vertex,1.0);    
    LightSpacePos = LightSpaceMatrix * WorldPos;
    WorldNormal = mat3(nm) * normal;
    Texcoord = texcoord;
    gl_Position = P * V * WorldPos;  
}