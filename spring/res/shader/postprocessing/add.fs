#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform sampler2D addTexture; // 带透明通道

in vec2 Texcoord;

void main()
{
    vec4 addColor = texture(addTexture,Texcoord);
    float sum = addColor.r + addColor.g + addColor.b;
    if( sum <= 0.0 )
    {
        FragColor = texture(Main_Texture,Texcoord);        
    }
    else
    {
        FragColor = addColor;
    }
}