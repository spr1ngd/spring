#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 30) out;

in VS_OUT{
    vec3 Normal;
} gs_in[];

uniform vec4 _Time;
uniform mat4 MVP;
out vec2 TexCoord;  

void genMesh( int index )
{ 
    vec3 pos = gl_in[index].gl_Position.xyz;
    vec3 N = gs_in[index].Normal;
    float random = sin(1.5707963 * fract(pos.x) + 1.5707963 * fract(pos.z));
    float randomCos = cos(1.5707963 * fract(pos.x) + 1.5707963 * fract(pos.z));
    float len = 0.08 * random;    
    float width = 0.005 * random;
    int subdivision = 5;
    float perLen = len / subdivision;
    float perUV = 1.0 / subdivision;

    float wind = abs(_Time.y) * randomCos;

    vec3 dir = vec3(1.0,0.0,0.0);
    for( int i = 0 ;i < subdivision ; i++ )
    {
        vec3 first = dir * width + N * perLen * i + width * dir * (i/subdivision * 0.5) * wind;
        vec2 firstUV = vec2(1.0, perUV * i);

        vec3 second = dir * width + N * perLen * (i + 1) + width *dir * ((i + 1)/subdivision * 0.5) * wind;
        vec2 secondUV = vec2(1.0, perUV * (i + 1));

        vec3 third = -dir * width + N * perLen * (i + 1) + width *-dir * (i + 1/subdivision * 0.5) * wind;
        vec2 thirdUV = vec2(0.0, perUV * (i + 1));
        
        vec3 fourth = -dir * width + N * perLen * i + width *-dir * (i/subdivision * 0.5) * wind;
        vec2 fourthUV = vec2(0.0, perUV * i);

        gl_Position = MVP *  vec4(pos + first,1.0);
        TexCoord = firstUV;
        EmitVertex();
        gl_Position = MVP * vec4(pos + second,1.0);
        TexCoord = secondUV;
        EmitVertex();
        gl_Position = MVP * vec4(pos + third,1.0);
        TexCoord = thirdUV;
        EmitVertex();
        EndPrimitive();

        gl_Position = MVP * vec4(pos + third,1.0);
        TexCoord = thirdUV;
        EmitVertex();
        gl_Position = MVP * vec4(pos + fourth,1.0);
        TexCoord = fourthUV;
        EmitVertex();
        gl_Position = MVP * vec4(pos + first,1.0);
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