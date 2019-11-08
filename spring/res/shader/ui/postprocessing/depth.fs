#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;

in vec2 Texcoord;
in vec4 Color;
in vec4 Vertex;

void main()
{
    vec4 depth = vec4(Vertex.z);
    FragColor = depth;
}