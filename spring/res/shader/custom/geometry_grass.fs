#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;

in vec2 TexCoord;

void main()
{
    vec4 texColor = texture(Main_Texture,TexCoord);
    FragColor = vec4(0.0,1.0 * (1.0 - TexCoord.y) ,0.0,1.0) * texColor;
}