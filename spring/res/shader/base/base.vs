#version 330 core

attribute vec3 vertex;

varying vec3 V_Vertex;

void main()
{
    V_Vertex = vertex;
    gl_Position = vec4(vertex,1.0);
}