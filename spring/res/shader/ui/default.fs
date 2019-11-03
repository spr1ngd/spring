#version 330 core

out vec4 FragColor;

uniform vec4 Main_Color;
uniform sampler2D Main_Texture;

in vec2 Texcoord;
in vec4 Color;

void main()
{
    vec4 texColor = texture(Main_Texture,Texcoord);
    FragColor = texColor;//* Color * Main_Color;
}