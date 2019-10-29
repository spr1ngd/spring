#version core 330
out vec4 FragColor;

uniform vec4 Main_Color;

in vec2 Texcoord;

void main()
{
    FragColor = Main_Color;
}