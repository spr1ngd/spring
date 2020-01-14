#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;

in vec2 Texcoord;

void main()
{
    FragColor =  texture(Main_Texture,Texcoord);
}