#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform sampler2D BrightTexture;

in vec2 Texcoord;

void main()
{
    vec4 mainColor = texture(Main_Texture,Texcoord);
    vec4 brightColor = texture(BrightTexture,Texcoord);
    FragColor = mainColor + brightColor;
}