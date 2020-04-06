#version 330 core

out vec4 FragColor;
in vec2 Texcoord;

uniform sampler2D Main_Texture;

void main()
{
    float depth = texture(Main_Texture,Texcoord).r;
    FragColor = vec4(vec3(depth),1.0);
}