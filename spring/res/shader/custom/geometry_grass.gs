#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 30) out;

in VS_OUT{
    vec4 WorldNormal;
} gs_in[];

out vec2 TexCoord; 

void genMesh( int index )
{
    vec3 helper = vec3(0.0,1.0,0.0);

    vec4 pos = gl_in[index].gl_Position;
    vec3 N = gs_in[index].WorldNormal.xyz;
    float len = 0.1;
    float width = 0.02;
    int subdivision = 5;
    float perLen = len / subdivision;
    float perUV = 1.0 / subdivision;

    vec3 dir = cross(N,helper);
    for( int i = 0 ;i < subdivision ; i++ )
    {
        vec3 first = dir * width + N * perLen * i;
        vec2 firstUV = vec2(1.0, perUV * i);
        vec3 second = dir * width + N * perLen * (i + 1);
        vec2 secondUV = vec2(1.0, perUV * (i + 1));
        vec3 third = -dir * width + N * perLen * (i + 1);
        vec2 thirdUV = vec2(0.0, perUV * (i + 1));
        vec3 fourth = -dir * width + N * perLen * i;
        vec2 fourthUV = vec2(0.0, perUV * i);

        gl_Position = pos + vec4(first,0.0);
        TexCoord = firstUV;
        EmitVertex();
        gl_Position = pos + vec4(second,0.0);
        TexCoord = secondUV;
        EmitVertex();
        gl_Position = pos + vec4(third,0.0);
        TexCoord = thirdUV;
        EmitVertex();
        EndPrimitive();

        gl_Position = pos + vec4(third,0.0);
        TexCoord = thirdUV;
        EmitVertex();
        gl_Position = pos + vec4(fourth,0.0);
        TexCoord = fourthUV;
        EmitVertex();
        gl_Position = pos + vec4(first,0.0);
        TexCoord = firstUV;
        EmitVertex();
        EndPrimitive();
    }
}

void main()
{
    genMesh(0);
    genMesh(1);
    genMesh(2);
}