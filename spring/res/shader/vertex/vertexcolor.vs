#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 V_VertexColor;

void main()
{
    V_VertexColor = vec4(vertex,1.0);
    gl_Position = P * V * M * vec4(vertex,1.0);
}