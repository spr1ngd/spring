#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 12) out;

in VS_OUT{
    vec3 Normal;
    vec2 UV;
} gs_in[];

uniform vec4 _Time;
uniform mat4 M;
uniform mat4 NM;
uniform mat4 MVP;
uniform vec3 WorldSpaceCameraPos;
uniform sampler2D HeightMap;

// 物理影响
uniform vec3 FactorPos;
const float FactorRadius = 0.15;

out vec2 TexCoord;

void genMesh( int index )
{ 
    vec3 pos = gl_in[index].gl_Position.xyz;
    float height = texture2D(HeightMap,gs_in[index].UV).r;
    pos += gs_in[index].Normal * height;
    vec3 WorldNormal = normalize((NM * vec4(gs_in[index].Normal,1.0)).xyz);
    vec4 WorldPos = M * vec4(pos,1.0);
    vec3 grassDirection = normalize(WorldSpaceCameraPos - WorldPos.xyz);
    // vec3 extentDirection = cross(grassDirection,vec3(0.0,1.0,0.0));
    vec3 extentDirection = cross(grassDirection,WorldNormal);

    // vec3 N = gs_in[index].Normal;
    vec3 N = WorldNormal;
    float random = sin(1.5707963 * fract(pos.x) + 1.5707963 * fract(pos.z));
    float randomCos = cos(1.5707963 * fract(pos.x) + 1.5707963 * fract(pos.z));
    float len = 0.1;    
    float width = 0.005;
    int subdivision = 5;
    float perLen = len / subdivision;
    float perUV = 1.0 / subdivision;

    float windRange = width * 2;
    float wind = _Time.y * 10;

    // 物理影响
    vec3 posOffset = WorldPos.xyz - FactorPos;
    float offsetDistance = sqrt(posOffset.x * posOffset.x + posOffset.y * posOffset.y + posOffset.z * posOffset.z);
    if( offsetDistance > FactorRadius )
    {
        posOffset = vec3(0.0);
    }   

    // vec3 dir = vec3(1.0,0.0,0.0);
    vec3 dir = extentDirection;
    // N = Normal;
    for( int i = 0 ; i <= subdivision ; i++ )
    {
        float windExtent = pow( i * 1.0 / subdivision,2.0);
        vec3 windOffset = windRange * dir * windExtent * wind;

        vec3 first = dir * width + N * perLen * i + windOffset;
        vec2 firstUV = vec2(1.0, perUV * i);

        vec3 vertexOffset = posOffset * i * 1.0 / subdivision;

        gl_Position = MVP * vec4(pos + first + vertexOffset,1.0);
        TexCoord = firstUV;
        EmitVertex();
        
        vec3 fourth = -dir * width + N * perLen * i + windOffset;
        vec2 fourthUV = vec2(0.0, perUV * i);
        
        gl_Position = MVP * vec4(pos + fourth + vertexOffset,1.0);
        TexCoord = fourthUV;
        EmitVertex();
    }
    EndPrimitive();
}

void main()
{
    genMesh(0);
    genMesh(1);
    genMesh(2);
}