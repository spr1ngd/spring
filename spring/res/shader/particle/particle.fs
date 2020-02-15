#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;

in vec2 Texcoord;
in vec4 Color;

void main()
{
    vec4 color = texture(Main_Texture,Texcoord);
    FragColor = Main_Color * Color * color;
}