#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;

in vec3 Normal;
in vec2 Texcoord;

void main()
{
    FragColor = texture(Main_Texture,Texcoord);
}