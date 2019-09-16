#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 NM;

out vec3 V_WorldNormal;
out vec2 V_Texcoord;

void main()
{
    V_WorldNormal = normal;
    V_Texcoord = texcoord;
    gl_Position = P * V * M * vec4(vertex,1.0);    
}