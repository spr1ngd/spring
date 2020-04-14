#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 100) out;

in VS_OUT
{
    vec3 vertex;
    vec4 pos;
    mat4 MVP;
} gs_in[];

out vec4 fColor;

const float NormalMagnitude = 0.5;

void drawNormal( int index )
{
    gl_Position = gs_in[index].pos;
    EmitVertex();
    gl_Position = gs_in[index].pos + vec4(1.0,0.0,0.0,0.0) * NormalMagnitude;
    EmitVertex();
    EndPrimitive();
}

void drawMesh( int index )
{
    mat4 MVP = gs_in[index].MVP;
    vec3 vertex = gs_in[index].vertex;
    float x = vertex.x;
    float y = vertex.y;
    if( x > 0 )
        return;
    int meshCount = 5;
    float offset = 1 / meshCount;
    if( y < 0 )
    {
        // 左下角
        fColor = vec4(1.0,0.0,0.0,1.0);
        for( int i = 0 ; i < meshCount; i++ )
        {
            vec4 start = vec4(vertex + vec3( 0.2 * i ,0.0,0.0),1.0);
            gl_Position = MVP * start;
            EmitVertex();
            vec4 end = start + vec4(1.0,0.0,0.0,1.0);
            gl_Position = MVP * end;
            EmitVertex();
            EndPrimitive();
        }
    }
    else
    {
        fColor = vec4(0.0,1.0,0.0,1.0);
        // 左上角
        for( int i = 0 ; i < meshCount; i++ )
        {
            vec4 start = vec4(vertex + vec3(0.0, 0.2 * i ,0.0),1.0);
            gl_Position = MVP * start;
            EmitVertex();
            vec4 end = start + vec4(0.0,1.0,0.0,1.0);
            gl_Position = MVP * end;
            EmitVertex();
            EndPrimitive();
        }
    }
}

void main()
{
    drawNormal(0);
    drawNormal(1);
    drawNormal(2);

    drawMesh(0);
    drawMesh(1);
    drawMesh(2);
}