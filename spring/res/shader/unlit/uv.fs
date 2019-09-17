#version 330 core
out vec4 FragColor;
in vec2 Texcoord;

void main()
{
    FragColor = vec4(Texcoord,0.0,1.0);
}