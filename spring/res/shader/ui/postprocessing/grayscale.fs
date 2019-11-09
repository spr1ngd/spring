#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texcoord;
in vec2 Texcoord;

void main()
{
    vec4 texColor = texture(Main_Texcoord,Texcoord);
    float average = 0.2126 * texColor.r + 0.7152 * texColor.g + 0.0722 * texColor.b;
    FragColor = vec4(average,average,average,1.0);
}