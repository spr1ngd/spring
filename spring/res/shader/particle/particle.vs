#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec4 color;
layout (location = 3) in vec4 transform;

uniform mat4 MVP;
uniform mat4 World2Object;
uniform vec3 WorldSpaceCameraPos;
uniform vec4 _Time;

out vec2 Texcoord;
out vec4 Color;
out vec4 Time;

void main()
{
    vec3 center = transform.xyz;
    float size = transform.w;

    // billboard算法
    vec3 view = (World2Object * vec4(WorldSpaceCameraPos,1.0)).xyz;
    view = normalize(view);
    vec3 up = abs(view.y) > 0.999 ? vec3(0.0,0.0,1.0) : vec3(0.0,1.0,0.0);
    vec3 right = normalize(cross(view,up));
    up = normalize(cross(view,right));

    
    float c = cos(_Time.x * 1 / transform.w);
    float s = sin(_Time.x * 1 / transform.w);
    mat3 rotate = mat3(c,-s,0,s,c,0,0,0,0); 
    vec3 rr = rotate * vertex;  

    vec3 offset = rr.xyz - center;
    vec3 pos = center + right * offset.x * size+ up * offset.y * size + view * offset.z * size;


    Texcoord = texcoord;
    Color = color;
    gl_Position = MVP * vec4(pos.xyz,1.0);
}