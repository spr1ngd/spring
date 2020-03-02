#version 330 core

out vec4 FragColor;

uniform vec4 identify;

void main()
{
    FragColor = identify;
}