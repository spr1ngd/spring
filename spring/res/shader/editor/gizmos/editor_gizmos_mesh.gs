#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT
{
    vec4 pos;
} gs_in[];

const float NormalMagnitude = 0.5;

void drawNormal( int index )
{
    gl_Position = gs_in[index].pos;
    EmitVertex();
    gl_Position = gs_in[index].pos + vec4(1.0,0.0,0.0,0.0) * NormalMagnitude;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    drawNormal(0);
    drawNormal(1);
    drawNormal(2);
}