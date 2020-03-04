#version 330 core

out vec4 FragColor;

uniform sampler2D Main_Texture;
uniform sampler2D outlineTexture;

in vec2 Texcoord;

void main()
{   
    vec4 mainColor = texture(Main_Texture,Texcoord);
    float sum = mainColor.r + mainColor.g + mainColor.b;
    if( sum <= 0.0f )
    {
        vec4 outlineColor = texture(outlineTexture,Texcoord);
        FragColor = outlineColor;
    }
    else
    {
        FragColor = vec4(0.0);
    }
}