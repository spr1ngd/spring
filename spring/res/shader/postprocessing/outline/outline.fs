#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform vec4 outlineColor;
uniform int outlineWidth;
in vec2 Texcoord;

void main()
{
    // TODO: 使用边缘检测的算法，只绘制边缘像素
    vec2 offet = 1.0 / textureSize(Main_Texture,0);
    vec4 color = texture(Main_Texture,Texcoord); 
    for( int x = -outlineWidth; x < outlineWidth; x++ )
    {
        for( int y = -outlineWidth; y < outlineWidth; y++ )
        {
            color += texture(Main_Texture,Texcoord + vec2(x,y));
        }
    }
    float sum = color.r + color.g + color.b;
    if( sum > 0.0 )
        FragColor = outlineColor;
    else
        FragColor = vec4(0.0,0.0,0.0,0.0);
}