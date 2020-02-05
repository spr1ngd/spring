#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 Main_Color;

in vec2 Texcoord;
in vec4 Color;

void main()
{
    // FragColor = texture(Main_Texture,Texcoord) * Main_Color * Color;
    FragColor = vec4(Color.rgb,0.2);
}