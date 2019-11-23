#version 330 core

layout (triangles) in;
layout (line_strip,max_vertices = 6) out;

in VS_OUT
{
    vec3 WorldNormal;
} gs_in[];

const float NormalMagnitude = 0.5;

void drawNormal( int index )
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].WorldNormal,0.0) * NormalMagnitude;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    drawNormal(0);
    drawNormal(1);
    drawNormal(2);
}