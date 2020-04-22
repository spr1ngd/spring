#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

// uniform mat4 NM;

out VS_OUT{
    vec3 Normal;
} vs_out;

void main()
{
    // vs_out.WorldNormal = MVP * vec4(normal,1.0);
    vs_out.Normal = normal;
    gl_Position = vec4(vertex,0.0);
}