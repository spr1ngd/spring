#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform sampler2D Secondary_Texture;

in vec2 Texcoord;

void main()
{
    vec4 mColor = texture(Main_Texture,Texcoord);
    vec4 sColor = texture(Secondary_Texture,Texcoord);
    FragColor = mColor * sColor;
}