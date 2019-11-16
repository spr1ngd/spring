#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;

in vec2 Texcoord;
in vec4 Color;

void main()
{
    vec4 texColor = texture(Main_Texture,vec2(Texcoord.s,1.0 - Texcoord.t));
    FragColor = vec4(texColor.r) * Color * Main_Color;
}